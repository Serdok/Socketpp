//
// Created on 5/3/20.
//

#include <arpa/inet.h>
#include "CommunicatingSocket.h"
#include "SocketExceptions.h"

namespace Socketpp {
    CommunicatingSocket::CommunicatingSocket( Type type, Protocol protocol )
    : Socket( type, protocol )
    {

    }

    CommunicatingSocket::CommunicatingSocket( socket_t socket )
    : Socket( socket )
    {
        setPeerAddress();
    }

    void CommunicatingSocket::setPeerAddress() {
        sockaddr_in addr{};
        socklen_t length = sizeof( addr );

        if (getpeername( m_socket, reinterpret_cast<sockaddr*>(std::addressof( addr )), std::addressof( length ) ) < 0) {
            throw SocketException( "Failed to get peer name" );
        }

        m_peer_address.setSocketAddress( IPv4Address( inet_ntoa( addr.sin_addr ) ), ntohs( addr.sin_port ) );
        (void) m_peer_address;
    }

    void CommunicatingSocket::connect( const SocketAddressV4& peer_address ) {
        m_peer_address = peer_address;
        const sockaddr addr = m_peer_address.toSockAddr();

        // Connect
        if (::connect( m_socket, std::addressof( addr ), sizeof( addr ) ) < 0) {
            throw SocketException( "Connection failed to " + m_peer_address.toString() );
        }
    }

    void CommunicatingSocket::send( const void* buffer, int size ) {
        if (::send( m_socket, buffer, size, 0 ) < 0) {
            throw SocketException( "Failed to send to " + m_peer_address.toString() );
        }
    }

    int CommunicatingSocket::recv( void* buffer, int size ) {
        int bytes_received;
        if ((bytes_received = ::recv( m_socket, buffer, size, 0 )) < 0) {
            throw SocketException( "Failed to receive from " + m_peer_address.toString() );
        }

        return bytes_received;
    }

    const SocketAddressV4& CommunicatingSocket::getPeerAddress() const {
        return m_peer_address;
    }
}