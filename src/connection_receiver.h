#pragma once
class connection_receiver
{
    class member;
    member* _m;
public:
    connection_receiver( );
    ~connection_receiver( );
    void run( );
};