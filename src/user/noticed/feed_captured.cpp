#include "feed_captured.h"
#include "boost/lexical_cast.hpp"
#include "user_default.h"
#include "utility.hpp"
#include "check_handle.h"
namespace user
{
namespace noticed
{
feed_captured::feed_captured( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void feed_captured::udp_receive_entry_point( network::network_handle handle, Json::Value const & root )
{
}
void feed_captured::tcp_receive_entry_point( network::client_handle handle, Json::Value const & root )
{
    utility::log( "エサがID[%d]番に食べられました。", _execute.user_handle_mgr( ).find_id( handle ) );
    cinder::app::console( ) << root["data"];

    int index = 0;
    Json::Value r;
    r["name"] = "feed_captured";

    for ( auto& obj : root["data"] )
    {
        int erase_tag = obj["tag"].asInt( );
        _execute.feed_mgr( ).remove( erase_tag );
        auto new_feed_data = _execute.feed_mgr( ).add_feed( );

        r["data"][index]["erase_tag"] = erase_tag;
        r["data"][index]["tag"] = new_feed_data->get_tag( );
        r["data"][index]["position"][0] = new_feed_data->get_position( ).x;
        r["data"][index]["position"][1] = new_feed_data->get_position( ).y;

        index++;
    }

    _execute.tcp( ).speech( Json::FastWriter( ).write( r ) );
}
}
}
