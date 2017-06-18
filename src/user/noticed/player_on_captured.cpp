#include "player_on_captured.h"
#include "find_room.h"
#include "check_handle.h"
#include "boost/lexical_cast.hpp"
#include "ground.h"
namespace user
{
namespace noticed
{
player_on_captured::player_on_captured( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void player_on_captured::udp_receive_entry_point( network::network_handle handle, Json::Value const & root )
{
}
void player_on_captured::tcp_receive_entry_point( network::client_handle handle, Json::Value const & root )
{
    auto check = std::dynamic_pointer_cast<check_handle>( _execute.find( "check_handle" ) );

    auto client = check->find_client( root["data"]["id"].asInt( ) );

    // 捕食したプレイヤーにスコアを提示します。
    {
        Json::Value r;
        r["name"] = "player_capture";
        r["data"]["score"] = root["data"]["score"];
        _execute.tcp( ).write( network::client_handle( client.ip_address, boost::lexical_cast<std::string>( client.tcp_port ) ),
                               Json::FastWriter( ).write( r ) );
    }
    
    // 送ってきた本人はそのまま死にます。
    {
        Json::Value r;
        r["name"] = "kill";
        _execute.tcp( ).write( handle, Json::FastWriter( ).write( r ) );
    }
}
}
}
