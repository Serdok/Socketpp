//
// Created on 5/3/20.
//

#ifndef SOCKET_IPV4ADDRESS_H
#define SOCKET_IPV4ADDRESS_H

#include <ostream>
#include <string>

namespace Socketpp {
    class IPv4Address {
    public:
        /**
         * Create an IPv4Address address from 4 bytes
         * @param x First byte of the address
         * @param y Second byte of the address
         * @param z Third byte of the address
         * @param w Fourth byte of the address
         */
        explicit IPv4Address( unsigned char x = 0, unsigned char y = 0, unsigned char z = 0, unsigned char w = 0 );

        /**
         * Create an IPv4Address address from a string
         * @param address IPv4Address string
         * @throws AddressParseError if the string is not an IPv4 address
         */
        explicit IPv4Address( const std::string& address );

        /**
         * Check if a string has the format of an IPv4 address
         * @param address The string to check
         * @return true if it is of the format x.y.z.w, false otherwise
         */
        static bool isIPv4( const std::string& address );

        /**
         * Set the IPv4 address
         * @param x First byte of the address
         * @param y Second byte of the address
         * @param z Third byte of the address
         * @param w Fourth byte of the address
         */
        void setIPv4Address( unsigned char x, unsigned char y, unsigned char z, unsigned char w );

        /**
         * Set the IPv4 address
         * @param address IPv4Address string
         * @throw AddressParseError if the string is not an IPv4 address
         */
        void setIPv4Address( const std::string& address );

        /**
         * Get the IPv4 address as a string
         */
        const std::string& toString() const;

    private:
        void checkStringFormat();

    private:
        std::string m_address;
    };

    std::ostream& operator <<( std::ostream& out, const IPv4Address& address );
}

#endif //SOCKET_IPV4ADDRESS_H
