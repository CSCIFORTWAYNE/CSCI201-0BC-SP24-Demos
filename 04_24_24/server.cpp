#include "PracticalSocket.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{

    try
    {
        TCPServerSocket servSock(9431);
        for (;;)
        {
            TCPSocket *sock = servSock.accept();
            std::cout << "incoming client: " << std::endl;
            uint32_t val;
            if (sock->recvFully(&val, sizeof(val)) == sizeof(val))
            {
                val = ntohl(val);
                std::cout << "receiving: " << val << " bytes" << std::endl;
                char *buffer = new char[val + 1];
                if (sock->recvFully(buffer, val) == val)
                {
                    buffer[val] = '\0';
                    std::string input(buffer);
                    std::cout << "received: " << input << std::endl;
                    val = htonl(val);
                    sock->send(&val, sizeof(val));
                    sock->send(buffer, val);
                }
                delete[] buffer;
            }
            delete sock;
        }
    }
    catch (SocketException e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}