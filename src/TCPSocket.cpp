//
// Created on 5/3/20.
//

#include "TCPSocket.h"

namespace Socketpp {
    TCPSocket::TCPSocket( socket_t socket )
    : CommunicatingSocket( socket )
    {

    }

    TCPSocket::TCPSocket()
    : CommunicatingSocket( Type::STREAM, Protocol::TCP )
    {

    }

    TCPSocket::TCPSocket( const SocketAddressV4& peer_address )
    : CommunicatingSocket( Type::STREAM, Protocol::TCP )
    {
        connect( peer_address );
    }
}