#pragma once
#include <string>
class network_handle
{
public:
    network_handle( std::string const& ip_address, int const& port );
public:
    // �댯�ȃR�s�[�����܂��B�����I��const���O���̂ŁB
    network_handle const& operator=( network_handle const& other ) const;
    bool operator==( network_handle const& other ) const;
    bool operator<( network_handle const& other ) const;
    bool operator<=( network_handle const& other ) const;
public: // �l�� network_factory �݂̂������������܂��B
    std::string const& ip_address;
    int const& port;
};
