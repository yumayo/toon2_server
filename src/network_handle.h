#pragma once
#include <string>
#include "network_object.h"
class network_handle
{
public:
    network_handle( std::string const& ip_address, int const& port );
    network_handle( network_object const& network_seed );
public:
    // �댯�ȃR�s�[�����܂��B�����I��const���O���̂ŁB
    network_handle const& operator=( network_handle const& other ) const;
    network_handle const& operator=( network_object const& other ) const;
    bool operator==( network_handle const& other ) const;
    bool operator<( network_handle const& other ) const;
    bool operator<=( network_handle const& other ) const;
public: // �l�͂��̃I�u�W�F�N�g�̍�҂̂݁A���������邱�Ƃ��ł��܂��B
    std::string const& ip_address;
    int const& port;
};
