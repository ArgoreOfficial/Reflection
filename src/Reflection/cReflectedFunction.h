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


template<typename F, F f>
class cReflectionHelper
{
public:
	struct creator
	{
		creator( const std::string _name )
		{
			cReflectionRegistry::reflectStatic( _name, (iArgOperator*)&( cReflectionHelper<F, f>::func ) );
		}
	};

	static const inline cReflectedFunction func{ f };
	static int id;
	static creator factory;
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
		printf( "Error: Expected %i arguments, got %i\n", (int)getArgCount(), (int)_args.size());

		return;
	}
	f( convertArg<Args>( _args.data()[ S ] )... );
}

