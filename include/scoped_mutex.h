#pragma once
#include "cinder/Noncopyable.h"
#include "recursion_usable_mutex.h"

// std::unique_lock<std::mutex>�ł���p�ł��邩�Ǝv�����̂ł����A
// lock(); lock(); ���ł��Ȃ������̂ŁA�g�p���Ȃ����Ƃɂ��܂����B
// �X�R�[�v���ŕʃX���b�h�͍쐬�ł��܂���B

// ���߂ȗ�
//scoped_mutex s( /*recursion_usable_mutex*/ mutex );
//std::thread thread( [ ] 
//{
//    scoped_mutex s( /*recursion_usable_mutex*/ mutex );
//} );
//thread.join( );

// �ǂ���
//{
//    scoped_mutex s( /*recursion_usable_mutex*/ mutex );
//}
//std::thread thread( [ ] 
//{
//    scoped_mutex s( /*recursion_usable_mutex*/ mutex );
//} );
//thread.join( );

namespace utility
{
class scoped_mutex : cinder::Noncopyable
{
    recursion_usable_mutex& _mutex;
public:
    scoped_mutex( recursion_usable_mutex& mutex );
    ~scoped_mutex( );
};
}
