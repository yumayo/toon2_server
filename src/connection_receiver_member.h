#pragma once
#include "connection_receiver.h"

// boost/Asioを使うためのマクロ。
// https://boostjp.github.io/tips/build_link.html
#define BOOST_DATE_TIME_NO_LIB
#define BOOST_REGEX_NO_LIB
#define BOOST_ERROR_CODE_HEADER_ONLY
#define BOOST_SYSTEM_NO_LIB

#include <asio/asio.hpp>
using udp = asio::ip::udp;
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include "string_utility.h"
class connection_receiver::member
{
    asio::io_service _io_service;
    udp::socket _udp_socket;
    udp::endpoint _reciving_endpoint;
    boost::array<char, 1024> _reciving_buffer;
    WriteOnDestroyed _update_log;
public:
    member( ) = delete;
    member( int const& port_num );
    void read( );
    void run( );
};