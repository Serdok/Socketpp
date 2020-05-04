//
// Created on 5/3/20.
//

#include "UDPSocket.h"
#include "SocketExceptions.h"

#include <arpa/inet.h>

namespace Socketpp {

    UDPSocket::UDPSocket()
    : CommunicatingSocket( Type::DATAGRAM, Protocol::UDP )
    {

    }

    UDPSocket::UDPSocket( unsigned short port )
    : CommunicatingSocket( Type::DATAGRAM, Protocol::UDP )
    {
        setAddress( SocketAddressV4( IPv4Address( "localhost" ), port ) );
    }

    UDPSocket::UDPSocket( const SocketAddressV4& address )
    : CommunicatingSocket( Type::DATAGRAM, Protocol::UDP )
    {
        setAddress( address );
    }

    void UDPSocket::disconnect() {
        sockaddr_in null_addr{};
        null_addr.sin_family = AF_UNSPEC;

        if (::connect( m_socket, reinterpret_cast<const sockaddr*>(std::addressof( null_addr )), sizeof( null_addr ) ) < 0) {
            if (errno != EAFNOSUPPORT) {
                throw SocketException( "Failed to disconnect" );
            }
        }
    }

    void UDPSocket::sendTo( const void* buffer, int size, const SocketAddressV4& peer_address ) {
        const sockaddr addr = peer_address.toSockAddr();
        if (::sendto( m_socket, buffer, size, 0, std::addressof( addr ), sizeof( addr ) ) < 0) {
            throw SocketException( "Failed to send to " + peer_address.toString() );
        }
    }

    int UDPSocket::recvFrom( void* buffer, int size, SocketAddressV4& source_address ) {
        sockaddr_in addr{};
        socklen_t length = sizeof( addr );

        int bytes_received;
        if ((bytes_received = recvfrom( m_socket, buffer, size, 0, reinterpret_cast<sockaddr*>(std::addressof( addr )), std::addressof( length ) )) < 0) {
            throw SocketException( "Failed to receive data" );
        }

        source_address.setSocketAddress( IPv4Address( inet_ntoa( addr.sin_addr ) ), ntohs( addr.sin_port ) );
        return bytes_received;
    }
}