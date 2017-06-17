#include "feed_captured.h"
#include "boost/lexical_cast.hpp"
#include "user_default.h"
#include "utility.hpp"
#include "check_handle.h"
namespace user
{
namespace noticed
{
std::pair<int, cinder::ivec2> feed_captured::create_feed( )
{
    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );
    auto feed_data = std::make_pair( ++_tag, cinder::vec2( _random_handle->nextInt( ground_size * ground_scale ), 
                                                           _random_handle->nextInt( ground_size * ground_scale ) ) );
    _feed_objects.insert( feed_data );
    return feed_data;
}
feed_captured::feed_captured( receive_data_execute& execute )
    : noticed_base( execute )
{
    _random_handle = std::make_shared<cinder::Rand>( 2017 );
    for ( int i = 0; i < 100; ++i ) create_feed( );
}
void feed_captured::udp_receive_entry_point( network::network_handle handle, Json::Value const & root )
{
}
void feed_captured::tcp_receive_entry_point( network::client_handle handle, Json::Value const & root )
{
    auto check = std::dynamic_pointer_cast<check_handle>( _execute.find( "check_handle" ) );

    utility::log( "エサがID[%d]番に食べられました。", check->find_id( handle.ip_address, boost::lexical_cast<int>( handle.port ) ) );
    cinder::app::console( ) << root["data"];
    cinder::app::console( ) << std::endl;

    int index = 0;
    Json::Value r;
    r["name"] = "feed_captured";

    for ( auto& obj : root["data"] )
    {
        int erase_tag = obj["tag"].asInt( );
        _feed_objects.erase( erase_tag );
        auto feed_data = create_feed( );

        r["data"][index]["erase_tag"] = erase_tag;
        r["data"][index]["tag"] = feed_data.first;
        r["data"][index]["position"][0] = feed_data.second.x;
        r["data"][index]["position"][1] = feed_data.second.y;

        index++;
    }

    _execute.tcp( ).speech( Json::FastWriter( ).write( r ) );
}
std::map<int, cinder::ivec2> const & feed_captured::get_feed_objects( ) const
{
    return _feed_objects;
}
}
}
