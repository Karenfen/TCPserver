#include "serverimpl.h"

#include <iostream>




servImpl::servImpl(const int& port, QObject* parent): QObject(parent),
    m_context(std::make_unique<boost::asio::io_context>()),
    m_acceptor(std::make_unique<tcp::acceptor>(*m_context, tcp::endpoint(tcp::v4(), port)))
{
     m_acceptor->set_option(tcp::acceptor::reuse_address(true));

}


void servImpl::start_accept()
{
    TCPconnection::smart_pointer new_klient = TCPconnection::create(*m_context);

//    m_acceptor.async_accept(new_klient->socket(), boost::bind(&TCPserver::handler, new_klient, std::placeholders::_1));  /* выдаёт ошибку... так и не разобрался*/

    m_acceptor->async_accept(new_klient->socket(),
        [this, new_klient] (const boost::system::error_code& error)
        {
            this->handler(new_klient, error);
        }
    );
}

void servImpl::run()
{
    start_accept();
    m_context->run();
};


std::string servImpl::m_get_name_client(const tcp::socket& klient_sock)
{
//    const socklen_t client_name_len = NI_MAXHOST;
//    char client_name_buf[client_name_len];

//    if(!getnameinfo(klient_sock, client_name_buf, client_name_len, NULL, 0, NI_NAMEREQD))
//        return client_name_buf;

    return "*****";
}


void servImpl::handler(TCPconnection::smart_pointer klient, const boost::system::error_code &error)
{
    if(!error)
    {
        std::cout << "start session..." << std::endl;

        try
        {
            klient->start();
        }
        catch (std::exception& e)
        {
            std::cerr << "Session is aborted!" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    }

    start_accept();
}
