target_sources(Socketpp PRIVATE SocketExceptions.cpp IPv4Address.cpp SocketAddressV4.cpp
        Socket.cpp CommunicatingSocket.cpp TCPSocket.cpp TCPServerSocket.cpp UDPSocket.cpp)
target_include_directories(Socketpp INTERFACE .)