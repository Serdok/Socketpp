//
// Created on 5/3/20.
//

#include "TCPServerSocket.h"
#include "TCPSocket.h"
#include "SocketExceptions.h"

namespace Socketpp {
    TCPServerSocket::TCPServerSocket( unsigned short port, int max_connections )
    : Socket( Type::STREAM, Protocol::TCP )
    {
        setAddress( SocketAddressV4( IPv4Address( "127.0.0.1" ), port ) );
        setMaxConnections( max_connections );
    }

    TCPServerSocket::TCPServerSocket( const SocketAddressV4& local_address, int max_connections )
    : Socket( Type::STREAM, Protocol::TCP )
    {
        setAddress( local_address );
        setMaxConnections( max_connections );
    }

    TCPSocket* TCPServerSocket::accept() {
        socket_t socket;
        sockaddr addr{}; socklen_t length = sizeof( addr );
        if ((socket = ::accept( m_socket, std::addressof( addr ), std::addressof( length ) )) < 0) {
            throw SocketException( "Failed to accept connection" );
        }

        return new TCPSocket( socket );
    }

    void TCPServerSocket::setMaxConnections( int max_connections ) {
        if (listen( m_socket, max_connections ) < 0) {
            throw SocketException( "Failed to listen from " + getAddress().toString() );
        }
    }
}