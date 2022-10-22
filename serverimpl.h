#pragma once


#include <memory>
#include <boost/asio.hpp>

#include "tcpconnection.h"




class servImpl
{
public:
    ~servImpl() = default;
    servImpl(const int& port);

protected:
    void start_accept();
    void run();

private:
    std::string m_get_name_client(const tcp::socket& klient_sock);
    void handler(TCPconnection::smart_pointer klient, const boost::system::error_code &error);
    
private:
    std::unique_ptr<boost::asio::io_context> m_context{};
    std::unique_ptr<tcp::acceptor> m_acceptor{};
    
    friend class TCPserver;
};

