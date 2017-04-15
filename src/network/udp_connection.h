#pragma once
#include "network_object.h"
#include "jsoncpp/json.h"
#include <functional>
#include "cinder/gl/scoped.h"
#include "scoped_mutex.h"
namespace network
{
class udp_connection
{
    class member;
    member* _m;
public:
    udp_connection( );
    udp_connection( int const& port_number );
    ~udp_connection( );
    void write( network_handle const& handle, Json::Value const& send_data );
    void write( network_handle const& handle, std::string const& send_data );
    void write( network_handle const& handle, char const* send_data );
    void write( network_handle const& handle, char const* send_data, size_t send_data_byte );
    void update( float delta_second );
    utility::recursion_usable_mutex& get_mutex( );
public:
    // �ʃX���b�h�ł̌Ăяo���Ȃ̂�mutex��t���ĕϐ��𑀍삵�Ă��������B
    // �T�|�[�g���Ă���t�H�[�}�b�g�� json �ł��B
    std::function<void( char const*, size_t )> on_received_not_support_format;
    // �ʃX���b�h�ł̌Ăяo���Ȃ̂�mutex��t���ĕϐ��𑀍삵�Ă��������B
    std::function<void( )> on_read_failed;

    std::function<void( )> on_sended;
    std::function<void( )> on_send_failed;
};
}
