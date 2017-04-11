#include "client_manager.h"
#include "string_utility.h"
#include "noticed_objects/find_room.h"
client_manager::client_manager( connection_server & server )
    : _server( server )
{
    regist_functions( );
}
client_manager::~client_manager( )
{
    for ( auto itr : _noticed_objects )
    {
        delete itr.second;
    }
    _noticed_objects.clear( );
}
void client_manager::receive_entry_point( std::string const & ip_address, int const & port, Json::Value const & root )
{
    auto handle = _network_handle_factory.make( ip_address, port );

    auto& function_name = root["NAME"];
    if ( function_name.isString( ) )
    {
        auto name = function_name.asString( );
        auto itr = _noticed_objects.find( name );
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
        log( "NAMEが見つからない不正なデータです。" );
    }
}
void client_manager::regist_functions( )
{
    #define regist_operation(_CLASS) _noticed_objects.insert( std::make_pair( #_CLASS, new _CLASS( _server ) ) )

    regist_operation( find_room );

    #undef regist_operation
}
