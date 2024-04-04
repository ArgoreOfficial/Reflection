#pragma once

#include <string>
#include <vector>
#include <map>

// keeping this here in case I need to reference it in the future
/*
template <std::size_t ... Is, typename F>
void ForEachIndex( std::index_sequence<Is...>, F&& f )
{
	int dummy[] = { 0, ( static_cast<void>( f( std::integral_constant<std::size_t, Is>() ) ), 0 )... };
	static_cast<void>( dummy ); // avoid warning for unused variable
}

template <std::size_t N, typename F>
void ForEachIndex( F&& f )
{
	ForEachIndex( std::make_index_sequence<N>(), std::forward<F>( f ) );
}
*/



// TYPE CONVERSION

template <typename T>
static T convertArg( std::string _str );

template<>
int convertArg<int>( std::string _str )
{
	return std::stoi( _str );
}


// FUNCTION CLASS

class iArgOperator
{
public:
	virtual void operator()( std::vector<std::string> _args ) = 0;
};

template<typename... Args>
class cReflectedFunction : iArgOperator
{
public:
	cReflectedFunction( void( *_f )( Args... ) ) { f = _f; }

	void( *f )( Args... );

	virtual void operator()( std::vector<std::string> _args ) override
	{
		auto sequence = std::index_sequence_for<Args...>{};
		handleImpl( sequence, _args.data() );
	}

private:
	template<std::size_t... S>
	void handleImpl( std::index_sequence<S...>, std::string* _args )
	{
		f( convertArg<Args>( _args[ S ] )... );
	}
};

// REFLECTION

struct sReflectionDescriptor
{
	int id;
	std::string name;
	std::string file;
	int line;
	iArgOperator* func;
};

class cReflectionRegistry
{
public:
	static std::map<std::string, sReflectionDescriptor> m_reflection_descriptors;
	
	inline static int registerReflection( const std::string _name, const std::string _file, int _line, iArgOperator* _func )
	{
		sReflectionDescriptor desc{
			.id   =  (int)m_reflection_descriptors.size(),
			.name = _name,
			.file = _file,
			.line = _line,
			.func = _func
		};

		m_reflection_descriptors[ desc.name ] = desc;
		return (int)m_reflection_descriptors.size();
	}

	inline static void callFunction( std::string _name, std::vector<std::string> _args = {} )
	{
		if ( m_reflection_descriptors.count( _name ) == 0 )
			return;

		iArgOperator* f = m_reflection_descriptors[ _name ].func;
		( *f )( _args );
	}
};
std::map<std::string, sReflectionDescriptor> cReflectionRegistry::m_reflection_descriptors = {};

// MACRO

#define FUNC_NAME_STR( _name ) #_name

#define REFLECT_STATIC( _f ) \
static cReflectedFunction func_##_f( _f ); \
static int id_##_f = cReflectionRegistry::registerReflection( #_f, __FILE__, __LINE__, (iArgOperator*)&( func_##_f ) );

#define REFLECT_STATIC_MEMBER( _c, _f ) \
static cReflectedFunction func_##_c ##_##_f( _c::_f ); \
static int id_##_c ##_##_f = cReflectionRegistry::registerReflection( FUNC_NAME_STR( _c::_f ), __FILE__, __LINE__, (iArgOperator*)&( func_ ##_c ##_ ##_f ) );
