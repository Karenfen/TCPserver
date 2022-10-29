#include "tcp_server.h"

#include <QApplication>
#include <iostream>
#include <cerrno>



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <port> " <<std::endl;
        return EXIT_FAILURE;
    }

    QApplication a(argc, argv);

//    try
//    {
        TCPserver server(std::stoi(argv[1]));

        server.start();

//    }  catch (const std::exception& e)
//    {
//        std::cerr << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }

    return a.exec();
}
