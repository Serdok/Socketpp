//
// Created on 5/3/20.
//

#ifndef SOCKET_SOCKETADDRESSV4_H
#define SOCKET_SOCKETADDRESSV4_H

#include "IPv4Address.h"

#include <netinet/in.h>

namespace Socketpp {
    class SocketAddressV4 {
    public:
        /**
         * Create a socket address
         * @param address IPv4 address of the socket
         * @param port Port number of the socket
         */
        explicit SocketAddressV4( const IPv4Address& address = IPv4Address(), unsigned short port = 0 );

        /**
         * Create a socket address
         * @param address IPv4 address of the socket
         * @param port Port number of the socket
         * @throw AddressParseError if the string is not a socket address
         */
        SocketAddressV4( const IPv4Address& address, const std::string& port );

        /**
         * Create a socket address from a string
         * @param address Socket address string
         * @throw AddressParseError if the string is not a socket address
         */
        explicit SocketAddressV4( const std::string& address );

        /**
         * Check if a string has the format of a socket address
         * @param address The string to check
         * @return true if it is of the format x.y.z.w:port, false otherwise
         */
        static bool isSocketAddrV4( const std::string& address );

        /**
         * Set a socket address
         * @param address IPv4 address of the socket
         * @param port Port number of the socket
         */
        void setSocketAddress( const IPv4Address& address, unsigned short port );

        /**
         * Create a socket address
         * @param address IPv4 address of the socket
         * @param port Port number of the socket
         * @throw AddressParseError if the string is not a socket address
         */
        void setSocketAddress( const IPv4Address& address, const std::string& port );

        /**
         * Create a socket address from a string
         * @param address Socket address string
         * @throw AddressParseError if the string is not a socket address
         */
        void setSocketAddress( const std::string& address );

        /**
         * Get the socket address as a string
         */
        const std::string& toString() const;

        /**
         * Get the IPv4 part of the socket address
         */
        IPv4Address getIPv4Address() const;

        /**
         * Get the port number of the socket address as a string
         */
        std::string getPortAsString() const;

        /**
         * Get the port number of the socket address as a number
         */
        unsigned short getPort() const;

        /**
         * Convert to C socket structure
         * @return A sockaddr structure filled with the correct info
         */
        sockaddr toSockAddr() const;

    private:
        void checkAddressFormat();

    private:
        std::string m_address;
    };

    std::ostream& operator <<( std::ostream& out, const SocketAddressV4& address );
}

#endif //SOCKET_SOCKETADDRESSV4_H
