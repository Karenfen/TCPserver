#include "tcp_server.h"

#include <iostream>
#include <cerrno>



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <port to ip4> " <<std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        TCPserver server(std::stoi(argv[1]));

        server.start();

    }  catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
