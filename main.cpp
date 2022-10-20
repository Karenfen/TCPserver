#include <QCoreApplication>

#include "tcp_server.h"



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <port to ip4> " <<std::endl;
        return EXIT_FAILURE;
    }

    QCoreApplication a(argc, argv);

    try
    {
        boost::asio::io_context context;

        TCPserver server(std::stoi(argv[1]), context);

        server.init();
        context.run();

    }  catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return a.exec();
}
