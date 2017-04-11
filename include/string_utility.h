#pragma once
#include <string>
#include "cinder/app/App.h"
std::string format( char const* format, ... );
void log( char const* str, ... );
void log_data( char const * data, size_t size );
class WriteOnDestroyed : public std::string
{
    std::string _filename;
public:
    WriteOnDestroyed( ) = delete;
    WriteOnDestroyed( std::string const& filename );
    ~WriteOnDestroyed( );
};
namespace cinder
{
namespace app
{
// データ書き出しのパスを取得
// ファイル書き出し時はこの関数でパスを取得する事
std::string getWritablePath( );
std::string loadString( std::string const& relative_path );
std::string getSystemTimeNamed( );
}
}