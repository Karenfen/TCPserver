#include "tcp_server.h"

#include <cstdlib>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <thread>
#include <boost/bind/bind.hpp>
#include <functional>



TCPserver::TCPserver(const int& port, boost::asio::io_context& context):
    /*m_port(port),*/ m_context(context), m_acceptor(m_context, tcp::endpoint(tcp::v4(), port))
{

}

void TCPserver::init()
{
    m_acceptor.set_option(tcp::acceptor::reuse_address(true));

    std::cout << "Server is running..." << std::endl;

    is_run = true;

    start_accept();
}

void TCPserver::start_accept()
{
    TCPconnection::smart_pointer new_klient = TCPconnection::create(m_context);

//    m_acceptor.async_accept(new_klient->socket(), boost::bind(&TCPserver::handler, new_klient, std::placeholders::_1));  /* выдаёт ошибку... так и не разобрался*/

    m_acceptor.async_accept(new_klient->socket(),
        [this, new_klient] (const boost::system::error_code& error)
        {
            this->handler(new_klient, error);
        }
     );
};


std::string TCPserver::m_get_name_client(const tcp::socket& klient_sock)
{
//    const socklen_t client_name_len = NI_MAXHOST;
//    char client_name_buf[client_name_len];

//    if(!getnameinfo(klient_sock, client_name_buf, client_name_len, NULL, 0, NI_NAMEREQD))
//        return client_name_buf;

    return "*****";
}

void TCPserver::handler(TCPconnection::smart_pointer klient, const boost::system::error_code &error)
{
    if(!error)
    {
        std::cout << "start session..." << std::endl;

        klient->start();
    }

    if(is_run)
        start_accept();
}









