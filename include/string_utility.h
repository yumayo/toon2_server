#pragma once
#include <string>
#include "cinder/app/App.h"
namespace utility
{
std::string format( char const* format, ... );
void log( char const* str, ... );
void log_with_time_stamp( char const* str, ... );
void log_network( std::string const& ip_address, int const& port, char const* str, ... );
void log_data( char const * data, size_t size );
}
namespace cinder
{
namespace app
{
// �f�[�^�����o���̃p�X���擾
// �t�@�C�������o�����͂��̊֐��Ńp�X���擾���鎖
std::string getWritablePath( );
std::string loadString( std::string const& relative_path );
std::string getSystemTimeNamed( );
}
}