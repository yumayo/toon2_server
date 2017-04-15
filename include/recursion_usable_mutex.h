#pragma once
#include <mutex>
#include <map>
#include <thread>

// �ċA�I�ȌĂяo������lock���|���Ȃ�mutex���Ǘ��ł��܂��B
// ��ɁAscoped_mutex�ƈꏏ�Ɏg���܂��B
namespace utility
{
class recursion_usable_mutex
{
    std::mutex _mutex;
    std::mutex _own_ids;
    std::map<std::thread::id, int /*�X���b�h�̔ԍ��̏d����*/> _ids;
public:
    void lock( );
    void unlock( );
    std::pair<std::map<std::thread::id, int>::iterator, bool> emplace( );
    void erase( );
    int& get_duplication_count( );
};
}
