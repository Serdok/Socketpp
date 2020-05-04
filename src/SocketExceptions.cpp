//
// Created on 5/2/20.
//

#include "SocketExceptions.h"

#include <utility>
#include <cstring>

namespace Socketpp {
    AddressParseError::AddressParseError( std::string faulty_address, std::string reason )
    : std::logic_error( reason.c_str() )
    {
        m_message = "Failed to parse address '" + std::move( faulty_address ) + "': " + std::move( reason );
    }

    const char* AddressParseError::what() const noexcept {
        return m_message.c_str();
    }



    SocketException::SocketException( std::string message, bool include_errno )
    : std::runtime_error( message.c_str() ), m_message( std::move( message ) )
    {
        if (include_errno) {
            m_message.append( ": " );
            m_message.append( strerror( errno ) );
        }
    }

    const char* SocketException::what() const noexcept {
        return m_message.c_str();
    }
}
