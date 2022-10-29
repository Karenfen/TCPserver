#include "tcp_server.h"

#include <iostream>
#include <exception>



TCPserver::TCPserver(const int& port): m_impl(new servImpl(port))
{
    if(!m_impl)
        throw std::logic_error("server initialization error!");
}


void TCPserver::start()
{
    std::cout << "Server is running..." << std::endl;

    m_impl->run();
}









