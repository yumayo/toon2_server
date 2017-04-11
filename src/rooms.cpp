#include "rooms.h"
#include "string_utility.h"
rooms::rooms( )
{
}
rooms::~rooms( )
{
    for ( auto itr : _noticed_objects )
    {
        delete itr.second;
    }
    _noticed_objects.clear( );
}
void rooms::receive_entry_point( std::string const & ip_address, int const & port, Json::Value const & root )
{
    auto handle = _network_handle_factory.make( ip_address, port );

    auto& function_name = root["NAME"];
    auto& function_data = root["DATA"];
    if ( function_name.isString( ) && function_data.isObject( ) )
    {
        auto itr = _noticed_objects.find( function_name.asString( ) );
        if ( itr != _noticed_objects.end( ) )
        {
            itr->second->receive_entry_point( handle, root );
        }
        else
        {
            log( "NAMEと一致する命令が見つかりませんでした。" );
        }
    }
    else
    {
        log( "NAMEとDATAが見つからない不正なデータです。" );
    }
}
void rooms::regist_functions( )
{
    #define regist_function(_CLASS) _noticed_objects.insert( std::make_pair( #_CLASS, new _CLASS( ) ) )

    #undef regist_function
}
