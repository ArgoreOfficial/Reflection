#pragma once

template <typename T>
static T convertArg( std::string _str );

template<> int         convertArg<int>( std::string _str ) { return std::stoi( _str ); }
template<> std::string convertArg<std::string>( std::string _str ) { return _str; }


template <typename T> 
static std::string getTypeName();
#define GEN_GETTYPENAME( _t ) template<> std::string getTypeName<_t>() { return #_t; }

template<typename T> 
inline std::string getTypeName() { return "Unknown type"; }

GEN_GETTYPENAME( int )
GEN_GETTYPENAME( bool )
GEN_GETTYPENAME( char )
GEN_GETTYPENAME( short )
GEN_GETTYPENAME( float )
GEN_GETTYPENAME( double )
GEN_GETTYPENAME( std::string )
GEN_GETTYPENAME( const char* )
