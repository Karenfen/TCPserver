#ifndef TCP_SERVER_H
#define TCP_SERVER_H


#include <algorithm>
#include <iostream>
#include <map>

#include <boost/asio.hpp>

#include "tcpconnection.h"
#include "serverimpl.h"




class TCPserver
{
public:
    TCPserver(const int& port, boost::asio::io_context& context);
    void init();

private:
    void start_accept();
    std::string m_get_name_client(const tcp::socket& klient_sock);
    void handler(TCPconnection::smart_pointer klient, const boost::system::error_code& error);

private:

    boost::asio::io_context& m_context;
    tcp::acceptor m_acceptor;
    bool is_run;

};

#endif // TCP_SERVER_H
