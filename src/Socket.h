//
// Created on 5/3/20.
//

#ifndef SOCKET_SOCKET_H
#define SOCKET_SOCKET_H

#include "SocketAddressV4.h"

#include <netdb.h>

namespace Socketpp {
    //! Type aliasing for socket file descriptors
    using socket_t = int;

    class Socket {
    public:
        //! Socket types
        enum Type { STREAM = SOCK_STREAM, DATAGRAM = SOCK_DGRAM, };

        //! Socket protocols
        enum Protocol { TCP = IPPROTO_TCP, UDP = IPPROTO_UDP, };

    public:
        //! Close connection
        virtual ~Socket();

        // FIXME Keep the copy operators deleted or defaulted?
        Socket( const Socket& ) = delete;
        Socket& operator =( const Socket& ) = delete;

        /**
         * Get this socket's address
         */
        const SocketAddressV4& getAddress() const;

        /**
         * Set this socket's address
         * @throw SocketException if binding fails
         */
        void setAddress( const SocketAddressV4& address );

        /**
         * Get the port number of a service
         * @param service The service name (ie. 'http')
         * @param protocol The protocol used by the service
         */
        static unsigned short resolveService( const std::string& service, Protocol protocol );

    protected:
        /**
         * Create a socket
         * @param type Type of the socket
         * @param protocol Protocol of the socket
         */
        Socket( Type type, Protocol protocol );

        /**
         * Create a socket
         * @param socket Existing socket file descriptor
         */
        explicit Socket( socket_t socket );

        socket_t m_socket = -1;

    private:
        SocketAddressV4 m_address;
    };
}

#endif //SOCKET_SOCKET_H
