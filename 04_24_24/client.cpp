#include "PracticalSocket.h"
#include <iostream>
#include <limits>
#include <string>

void resetStream();

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        // 127.0.0.1 works on WSL ::1 works on windows.
        std::cerr << "Usage: ./client <server host>" << std::endl;
        return 1;
    }

    try
    {
        std::cout << argv[1] << std::endl;
        TCPSocket sock(argv[1], 9431);

        std::string message;
        std::cout << "Enter a message for the server: ";
        std::getline(std::cin >> std::ws, message);

        uint32_t val = htonl(message.length());

        sock.send(&val, sizeof(val));
        sock.send(message.c_str(), message.length());
        if (sock.recvFully(&val, sizeof(val)) == sizeof(val))
        {
            val = ntohl(val);
            char *buffer = new char[val + 1];
            if (sock.recvFully(buffer, val) == val)
            {
                buffer[val] = '\0';
                std::cout << "Server Response: " << buffer << std::endl;
            }
            delete[] buffer;
        }
    }
    catch (SocketException e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}