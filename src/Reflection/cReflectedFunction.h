#pragma once

#include <vector>
#include <string>
#include "cReflectionRegistry.h"
#include "ArgConvert.h"

class iArgOperator
{
public:
	virtual void operator()( const std::vector<std::string>& _args ) = 0;
	virtual int getArgCount() = 0;
	virtual std::vector<std::string> getArgsTypeNames() = 0;
};

template<typename... Args>
class cReflectedFunction : iArgOperator
{
public:
	cReflectedFunction( void( *_f )( Args... ) ) { f = _f; }

	virtual void operator()( const std::vector<std::string>& _args ) override;
	virtual int getArgCount() override { return (int)sizeof...( Args ); }
	virtual std::vector<std::string> getArgsTypeNames() override;

private:
	template<std::size_t... S>
	void handleImpl( std::index_sequence<S...>, const std::vector<std::string>& _args );

	void( *f )( Args... );
};


template<auto f, class F = decltype( *f )>
struct Reflect
{
	Reflect( const std::string _name )
	{
		static cReflectedFunction func( f );
		cReflectionRegistry::reflectStatic( _name, (iArgOperator*)( &func ) );
	}
};

template<auto f, class F = decltype( *f )>
class Reflector
{
public:
	static Reflect<f, F> creator;
};



template<typename ...Args>
inline void cReflectedFunction<Args...>::operator()( const std::vector<std::string>& _args )
{
	handleImpl( std::index_sequence_for<Args...>{}, _args );
}

template<typename ...Args>
inline std::vector<std::string> cReflectedFunction<Args...>::getArgsTypeNames()
{
	return std::vector<std::string>{ getTypeName<Args>()... };
}

template<typename ...Args>
template<std::size_t ...S>
inline void cReflectedFunction<Args...>::handleImpl( std::index_sequence<S...>, const std::vector<std::string>& _args )
{
	if ( getArgCount() != (int)_args.size() )
	{
		printf( "Error: Expected %i arguments, got %i", (int)getArgCount(), (int)_args.size());

		return;
	}
	f( convertArg<Args>( _args.data()[ S ] )... );
}

