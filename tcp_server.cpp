#include "tcp_server.h"

#include <iostream>
#include <exception>



TCPserver::TCPserver(const int& port): m_impl(std::make_unique<servImpl>(port))
{

}


void TCPserver::start()
{
    if(!m_impl)
        throw std::logic_error("server initialization error!");

    std::cout << "Server is running..." << std::endl;

    m_impl->run();
}









