#pragma once
#include "connection_server.h"

// boost/Asioを使うためのマクロ4つ分。
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

    // UDPを使う上で必須の項目達。
    asio::io_service _io_service;
    udp::socket _udp_socket;
    udp::endpoint _remote_endpoint;
    boost::array<char, 2048> _remote_buffer;

    // 繋がったオブジェクトたちを保存しておきます。
    client_manager _client_manager;
public:
    member( ) = delete;
    member( connection_server& parent, int const& port_num );
    // この関数を呼ぶと受信したデータをすべて読み込みます。
    // またデータが来るまで待機します。
    void run( );

    void write( network_handle  const& handle, Json::Value const& send_data );
private:
    // エントリーポイント
    void read( );
};