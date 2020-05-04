//
// Created on 5/2/20.
//

#ifndef SOCKET_SOCKETEXCEPTIONS_H
#define SOCKET_SOCKETEXCEPTIONS_H

#include <stdexcept>

namespace Socketpp {
    class AddressParseError : std::logic_error {
    public:
        explicit AddressParseError( std::string faulty_address, std::string reason );
        ~AddressParseError() noexcept override = default;

        const char* what() const noexcept override;

    private:
        std::string m_message;
    };



    class SocketException : public std::runtime_error {
    public:
        explicit SocketException( std::string message, bool include_errno = true );
        ~SocketException() noexcept override = default;

        const char* what() const noexcept override;

    private:
        std::string m_message;
    };
}

#endif //SOCKET_SOCKETEXCEPTIONS_H
