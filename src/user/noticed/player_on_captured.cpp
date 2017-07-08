#include "player_on_captured.h"
#include "find_room.h"
#include "check_handle.h"
#include "ground.h"
namespace user
{
namespace noticed
{
player_on_captured::player_on_captured( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void player_on_captured::udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const & root )
{
}
void player_on_captured::tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const & root )
{
    auto client = _execute.user_handle_mgr( ).find_client( root["data"]["id"].asInt( ) );

    // 捕食したプレイヤーにスコアを提示します。
    {
        Json::Value r;
        r["name"] = "player_capture";
        r["data"]["score"] = root["data"]["score"];
        _execute.tcp( ).write( treelike::network::network_handle( client.second->second.ip_address, client.second->second.tcp_port ),
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
