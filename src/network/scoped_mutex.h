#pragma once
#include "cinder/Noncopyable.h"
#include <mutex>
#include "cinder/gl/scoped.h"
// cinder/gl/scoped.h ���Q�l�ɂ��܂����B

namespace network
{
// �C���X�^���X�����邾���ł��̃X�R�[�v���̂݃u���b�L���O���܂��B
class scoped_mutex : cinder::Noncopyable
{
    std::mutex& _mutex;
public:
    scoped_mutex( ) = delete;
    scoped_mutex( std::mutex& server_mutex );
    ~scoped_mutex( );
};
}
