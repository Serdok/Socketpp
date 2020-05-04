//
// Created on 5/3/20.
//

#ifndef SOCKET_TCPSOCKET_H
#define SOCKET_TCPSOCKET_H

#include "CommunicatingSocket.h"
#include "TCPServerSocket.h"

namespace Socketpp {
    class TCPSocket : public CommunicatingSocket {
    public:
        /**
         * Create a TCP socket in an unconnected state
         */
        TCPSocket();

        /**
         * Create a TCP socket in a connected state
         * @param peer_address The address of the peer to connect to
         * @throw SocketException if connecting failed
         */
        explicit TCPSocket( const SocketAddressV4& peer_address );

    private:
        friend TCPServerSocket; // Give access to below constructor
        explicit TCPSocket( socket_t socket );
    };
}

#endif //SOCKET_TCPSOCKET_H
