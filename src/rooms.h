#pragma once
#include "noticed_objects/noticed_base_object.h"
#include "network_factory.h"
#include "write_on_destroyed.h"
class rooms
{
    network_factory _network_handle_factory;

    // 文字列から命令を実行するためのもの。
    std::map<std::string, noticed_base_object*> _noticed_objects;
public:
    rooms( );
    ~rooms( );
    // 呼び出したい関数を全て登録します。
    void regist_functions( );
    void receive_entry_point( std::string const& ip_address, int const& port, Json::Value const& root );
};