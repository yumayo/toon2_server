#pragma once
#include "connection_server.h"

// boost/Asio���g�����߂̃}�N��4���B
// https://boostjp.github.io/tips/build_link.html
#define BOOST_DATE_TIME_NO_LIB
#define BOOST_REGEX_NO_LIB
#define BOOST_ERROR_CODE_HEADER_ONLY
#define BOOST_SYSTEM_NO_LIB
#include <asio/asio.hpp>
using udp = asio::ip::udp;

#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>

#include "client_manager.h"

#include <thread>

class connection_server::member
{
    connection_server& _server;

    // UDP���g����ŕK�{�̍��ڒB�B
    asio::io_service _io_service;
    udp::socket _udp_socket;
    udp::endpoint _remote_endpoint;
    boost::array<char, 2048> _remote_buffer;
    int const _port_number;

    // �񓯊��I�Ɏ�M�����Ȃ��ƃv���O�������~�܂��Ă��܂��̂ŁB
    std::thread _update_io_service;
    bool _is_update = true;
    std::mutex _mutex;

    // �q�������I�u�W�F�N�g������ۑ����Ă����܂��B
    client_manager _client_manager;
public:
    member( ) = delete;
    member( connection_server& server, int const& port_num );
    ~member( );
    
    void write( network_handle const& handle, Json::Value const& send_data );

    void update( float delta_second );

    std::mutex& get_mutex( );
private:
    // �G���g���[�|�C���g
    void _read( );
    // �f�[�^����M�����Ƃ��ɌĂ΂�܂��B
    void _on_received( size_t bytes_transferred );
    void _kill( );
};