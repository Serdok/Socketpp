//
// Created on 5/3/20.
//

#include "Socket.h"
#include "SocketExceptions.h"

#include <sys/socket.h>
#include <unistd.h>

namespace Socketpp {
    Socket::Socket( Type type, Protocol protocol ) {
        if ((m_socket = socket( AF_INET, type, protocol )) < 0) {
            throw SocketException( "Failed to create socket" );
        }

        int opt = 1;
        if (setsockopt( m_socket, SOL_SOCKET, SO_REUSEADDR, std::addressof( opt ), sizeof( opt ) ) < 0) {
            throw SocketException( "Failed to set socket option" );
        }
    }

    Socket::Socket( socket_t socket )
    : m_socket( socket )
    {

    }

    Socket::~Socket() {
        close( m_socket );
    }

    const SocketAddressV4& Socket::getAddress() const {
        return m_address;
    }

    void Socket::setAddress( const SocketAddressV4& address ) {
        m_address = address;

        // Bind the socket
        const sockaddr addr = m_address.toSockAddr();
        if (bind( m_socket, std::addressof( addr ), sizeof( addr ) ) < 0) {
            throw SocketException( "Failed to bind socket to " + address.toString() );
        }
    }

    unsigned short Socket::resolveService( const std::string& service, Protocol protocol ) {
        const std::string prot = [=]() {
            switch (protocol) {
                case Protocol::TCP: return "tcp";
                case Protocol::UDP: return "udp";
                default: return "";
            }
        }();

        servent* serv;
        if ((serv = getservbyname( service.c_str(), prot.c_str() )) == nullptr) {
            return std::strtol( service.c_str(), nullptr, 10 );
        }

        return ntohs( serv->s_port );
    }
}