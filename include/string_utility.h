#pragma once
#include <string>
#include <mutex>
#include "cinder/app/App.h"
extern std::mutex gloval_app_console_mutex;
std::string format( char const* format, ... );
void log( char const* str, ... );
void log_with_time_stamp( char const* str, ... );
void log_data( char const * data, size_t size );
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