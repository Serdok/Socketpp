//
// Created on 5/3/20.
//

#ifndef SOCKET_TCPSERVERSOCKET_H
#define SOCKET_TCPSERVERSOCKET_H

#include "Socket.h"

namespace Socketpp {
    class TCPSocket;

    class TCPServerSocket : public Socket {
    public:
        /**
         * Create a TCP server socket
         * @param port The port to use by the server to listen from
         * @param max_connections The maximum number of connections the server can support (default: 5)
         * @throw SocketException if creation failed
         */
        explicit TCPServerSocket( unsigned short port, int max_connections = 5 );

        /**
         * Create a TCP server socket
         * @param local_address The address of the server it will use to listen from
         * @param max_connections The maximum number of connections the server can support (default: 5)
         * @throw SocketException if creation failed
         */
        explicit TCPServerSocket( const SocketAddressV4& local_address, int max_connections = 5 );

        /**
         * Accept a new connection
         * @return A connection handler
         * @throw SocketException if accepting failed
         */
        TCPSocket* accept();

    private:
        void setMaxConnections( int max_connections );
    };
}

#endif //SOCKET_TCPSERVERSOCKET_H
