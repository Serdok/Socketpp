//
// Created on 5/3/20.
//

#include "SocketAddressV4.h"
#include "SocketExceptions.h"

#include <netdb.h>
#include <regex>

namespace Socketpp {
    SocketAddressV4::SocketAddressV4( const IPv4Address& address, unsigned short port ) {
        setSocketAddress( address, port );
    }

    void SocketAddressV4::setSocketAddress( const IPv4Address& address, unsigned short port ) {
        m_address = address.toString() + ':' + std::to_string( port );
    }

    SocketAddressV4::SocketAddressV4( const IPv4Address& address, const std::string& port ) {
        setSocketAddress( address, port );
    }

    void SocketAddressV4::setSocketAddress( const IPv4Address& address, const std::string& port ) {
        m_address = address.toString() + ':' + port;
        checkAddressFormat();
    }

    SocketAddressV4::SocketAddressV4( const std::string& address ) {
        setSocketAddress( address );
    }

    void SocketAddressV4::setSocketAddress( const std::string& address ) {
        m_address = address;
        checkAddressFormat();
    }

    bool SocketAddressV4::isSocketAddrV4( const std::string& address ) {
        // Capturing groups?
        const std::regex address_format( R"(^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}:\d{1,5}$)" );
        if (!std::regex_match( address, address_format )) {
            return false;
        }

        // Correct format, check that each ip number is 1 byte long
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

        // No more '.', index points at the last byte of the ip address
        next = address.find( ':', index );
        index = next + 1;
        char* start = const_cast<char*>(address.c_str() + index);
        long port = std::strtol( start, nullptr, 10 );

        // Check that number is below 65535
        return port <= std::numeric_limits< unsigned short >::max();
    }

    void SocketAddressV4::checkAddressFormat() {
        if (!isSocketAddrV4( m_address )) {
            throw AddressParseError( m_address, "Wrong IPv4 socket address format" );
        }
    }

    const std::string& SocketAddressV4::toString() const {
        return m_address;
    }

    IPv4Address SocketAddressV4::getIPv4Address() const {
        return IPv4Address( m_address.substr( 0, m_address.find_first_of( ':' ) ) );
    }

    std::string SocketAddressV4::getPortAsString() const {
        return m_address.substr( m_address.find_first_of( ':' ) + 1 );
    }

    unsigned short SocketAddressV4::getPort() const {
        return std::strtol( getPortAsString().c_str(), nullptr, 10 );
    }

    sockaddr SocketAddressV4::toSockAddr() const {
        // Resolve name
        auto address = getIPv4Address().toString();
        auto port = getPortAsString();

        addrinfo* info = nullptr;
        addrinfo hints{};
        hints.ai_family = AF_INET;      // Ipv4
        hints.ai_flags = AI_PASSIVE;

        int code;
        if ((code = getaddrinfo( address.c_str(), port.c_str(), std::addressof( hints ), std::addressof( info ) )) < 0) {
            throw SocketException( gai_strerror( code ), false );
        }

        return *info->ai_addr;
    }

    std::ostream& operator <<( std::ostream& out, const SocketAddressV4& address ) {
        return out << address.toString();
    }
}