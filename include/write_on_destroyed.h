#pragma once
#include <string>
class write_on_destroyed : public std::string
{
    std::string _filename;
public:
    write_on_destroyed( ) = delete;
    write_on_destroyed( std::string const& filename );
    ~write_on_destroyed( );
    void operator()( char const* str, ... );
};