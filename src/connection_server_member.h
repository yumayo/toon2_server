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

class connection_server::member
{
    connection_server& _parent;

    // UDP���g����ŕK�{�̍��ڒB�B
    asio::io_service _io_service;
    udp::socket _udp_socket;
    udp::endpoint _remote_endpoint;
    boost::array<char, 2048> _remote_buffer;

    // �q�������I�u�W�F�N�g������ۑ����Ă����܂��B
    client_manager _client_manager;
public:
    member( ) = delete;
    member( connection_server& parent, int const& port_num );
    // ���̊֐����ĂԂƎ�M�����f�[�^�����ׂēǂݍ��݂܂��B
    // �܂��f�[�^������܂őҋ@���܂��B
    void run( );

    void write( network_handle  const& handle, Json::Value const& send_data );
private:
    // �G���g���[�|�C���g
    void read( );
};