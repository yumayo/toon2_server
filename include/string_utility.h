#pragma once
#include <string>
#include <mutex>
#include "cinder/app/App.h"
extern std::mutex glocal_log_mutex;
std::string format( char const* format, ... );
void log( char const* str, ... );
void log_data( char const * data, size_t size );
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