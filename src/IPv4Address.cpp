//
// Created on 5/3/20.
//

#include "IPv4Address.h"
#include "SocketExceptions.h"

#include <cstring>
#include <regex>

namespace Socketpp {
    IPv4Address::IPv4Address( unsigned char x, unsigned char y, unsigned char z, unsigned char w ) {
        setIPv4Address( x, y, z, w );
    }

    void IPv4Address::setIPv4Address(unsigned char x, unsigned char y, unsigned char z, unsigned char w) {
        std::ostringstream ss;
        ss << std::to_string( x ) << '.' << std::to_string( y )
           << '.' << std::to_string( z ) << '.' << std::to_string( w );
        m_address = ss.str();
    }

    IPv4Address::IPv4Address( const std::string& address ) {
        setIPv4Address( address );
    }

    void IPv4Address::setIPv4Address(const std::string &address) {
        m_address = address;
        checkStringFormat();
    }

    bool IPv4Address::isIPv4( const std::string& address ) {
        // Capturing groups?
        const std::regex address_format( R"(^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$)" );
        if (!std::regex_match( address, address_format )) {
            return false;
        }

        // Correct format, check that each number is 1 byte long
        int index = 0;
        int next = address.find( '.', index );
        while (next != std::string::npos) {
            char* start = const_cast<char*>(address.c_str() + index);
            char* end = const_cast<char*>(address.c_str() + next);
            long byte = std::strtol( start, std::addressof( end ), 10 );
            if (byte > std::numeric_limits< unsigned char >::max()) {
                // Number is over 255
                return false;
            }

            index = next + 1;
            next = address.find( '.', index );
        }

        return true;
    }

    void IPv4Address::checkStringFormat() {
        if (!isIPv4( m_address )) {
            throw AddressParseError( m_address, "Wrong IPv4 address format" );
        }
    }

    const std::string& IPv4Address::toString() const {
        return m_address;
    }

    std::ostream& operator <<( std::ostream& out, const IPv4Address& address ) {
        return out << address.toString();
    }
}