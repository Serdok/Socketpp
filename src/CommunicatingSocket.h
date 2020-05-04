//
// Created on 5/3/20.
//

#ifndef SOCKET_COMMUNICATINGSOCKET_H
#define SOCKET_COMMUNICATINGSOCKET_H

#include "Socket.h"

namespace Socketpp {
    class CommunicatingSocket : public Socket {
    public:
        /**
         * Connect to a remote host
         * @param peer_address The address of the peer
         * @throw SocketException if connection failed
         */
        void connect( const SocketAddressV4& peer_address );

        /**
         * Send data to the remote host
         * @param buffer The data to send
         * @param size Number of bytes to send
         * @throw SocketException if sending failed
         */
        void send( const void* buffer, int size );

        /**
         * Receive data from the remote host
         * @param buffer The data that has been received
         * @param size The number of bytes to receive
         * @return The actual number of bytes received
         * @throw SocketException if receiving failed
         */
        int recv( void* buffer, int size );

        /**
         * Get the peer's address
         */
        const SocketAddressV4& getPeerAddress() const;

    protected:
        /**
         * Create a communicating socket
         * @param type Type of the socket
         * @param protocol Protocol of the socket
         */
        CommunicatingSocket( Type type, Protocol protocol );

        /**
         * Create a communicating socket
         * @param socket Existing socket file descriptor
         */
        explicit CommunicatingSocket( socket_t socket );

    private:
        void setPeerAddress();

    private:
        SocketAddressV4 m_peer_address;
    };
}

#endif //SOCKET_COMMUNICATINGSOCKET_H
