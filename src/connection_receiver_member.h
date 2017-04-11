#pragma once
#include "connection_receiver.h"

// boost/Asio���g�����߂̃}�N���B
// https://boostjp.github.io/tips/build_link.html
#define BOOST_DATE_TIME_NO_LIB
#define BOOST_REGEX_NO_LIB
#define BOOST_ERROR_CODE_HEADER_ONLY
#define BOOST_SYSTEM_NO_LIB

#include <asio/asio.hpp>
using udp = asio::ip::udp;
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include "jsoncpp/json.h"
#include "rooms.h"
class connection_receiver::member
{
    // UDP���g����ŕK�{�̍��ڒB�B
    asio::io_service _io_service;
    udp::socket _udp_socket;
    udp::endpoint _remote_endpoint;
    boost::array<char, 1024> _remote_buffer;

    // �q�������I�u�W�F�N�g������ۑ����Ă����܂��B
    rooms _rooms;
public:
    member( ) = delete;
    member( int const& port_num );
    // ���̊֐����ĂԂƎ�M�����f�[�^�����ׂēǂݍ��݂܂��B
    // �܂��f�[�^������܂őҋ@���܂��B
    void run( );
private:
    // �G���g���[�|�C���g
    void read( );
};