//
// Created on 5/3/20.
//

#ifndef SOCKET_UDPSOCKET_H
#define SOCKET_UDPSOCKET_H

#include "CommunicatingSocket.h"

namespace Socketpp {
    class UDPSocket : public CommunicatingSocket {
    public:
        /**
         * Create a UDP socket in an unconnected state
         */
        UDPSocket();

        /**
         * Create an UDP socket in a connected state
         * @param port The port to listen from
         * @throw SocketException if binding failed
         */
        explicit UDPSocket( unsigned short port );

        /**
         * Create an UDP socket in a connected state
         * @param address The address to listen from
         * @throw SocketException if binding failed
         */
        explicit UDPSocket( const SocketAddressV4& address );

        /**
         * Set the socket to an unconnected state
         * @throw SocketException if disconnecting failed
         */
        void disconnect();

        /**
         * Send data to another host
         * @param buffer The data to send
         * @param size The number of bytes to send
         * @param peer_address The address of the receiver
         * @throw SocketException if sending failed
         */
        void sendTo( const void* buffer, int size, const SocketAddressV4& peer_address );

        /**
         * Receive data from a host
         * @param buffer The data that has been received
         * @param size The number of bytes to receive
         * @param source_address The address of the sender
         * @return The actual number of bytes received
         * @throw SocketException if receiving failed
         */
        int recvFrom( void* buffer, int size, SocketAddressV4& source_address );

    private:

    };
}

#endif //SOCKET_UDPSOCKET_H
