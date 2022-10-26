#include "serverimpl.h"

#include <iostream>
#include <QAbstractSocket>
#include <exception>
#include <QApplication>




servImpl::servImpl(const int& port, QObject* parent):
    QObject(parent), server_ipV4(new QTcpServer()), server_ipV6(new QTcpServer()), port_(port)
{
    if(!server_ipV4 || !server_ipV6)
    {
        throw std::runtime_error("Initialization error!");
    }

    connect(server_ipV4.get(), &QTcpServer::acceptError, this, &servImpl::accept_error_handler);
    connect(server_ipV6.get(), &QTcpServer::acceptError, this, &servImpl::accept_error_handler);
    connect(server_ipV4.get(), &QTcpServer::newConnection, this, &servImpl::accept_connection);
    connect(server_ipV6.get(), &QTcpServer::newConnection, this, &servImpl::accept_connection);


}


void servImpl::run()
{
    if(!server_ipV4->listen(QHostAddress::LocalHost, port_))
        std::cerr << "Listening server ip v4 error!" << std::endl;

    if(!server_ipV6->listen(QHostAddress::LocalHostIPv6, port_))
        std::cerr << "Listening server ip v6 error!" << std::endl;

    if(!server_ipV4->isListening() && !server_ipV6->isListening())
        throw std::logic_error(server_ipV4->errorString().toStdString() + " / " + server_ipV6->errorString().toStdString());

    std::cout << "Server IP4 is listening address ("
              <<  server_ipV4->serverAddress().toString().toStdString()
              << ") port: " << server_ipV4->serverPort() << std::endl;

    std::cout << "Server IP6 is listening address ("
              <<  server_ipV6->serverAddress().toString().toStdString()
              << ") port: " << server_ipV6->serverPort() << std::endl;
}


void servImpl::accept_connection()
{
    auto klient_socket = qobject_cast<QTcpServer*>(sender())->nextPendingConnection();

    if(klient_socket)
    {
        std::cout << "Colient: "
                  << klient_socket->peerName().toStdString()
                  << " with address: "
                  << klient_socket->peerAddress().toString().toStdString()
                  << " connected from port: "
                  << klient_socket->peerPort()
                  << std::endl;

        auto klient = new TCPconnection(klient_socket, this);

        connect(klient, &TCPconnection::connection_is_aborted, this, &servImpl::delet_klient);
        connect(klient, &TCPconnection::close_server, this, &servImpl::shutdown);
    }
}


void servImpl::accept_error_handler(QAbstractSocket::SocketError socket_error)
{
    std::cerr << "Accept error! " << socket_error << std::endl;
    qobject_cast<QTcpServer>(sender()).resumeAccepting();
}


void servImpl::delet_klient(TCPconnection *klient)
{
    std::cout << "Connection with client ("
              << klient->get_info()
              << ") aborted" << std::endl;

    delete klient;
}


void servImpl::shutdown(TCPconnection *klient)
{
    delet_klient(klient);

    std::cout << "Server shuts down..." << std::endl;

    server_ipV4->close();
    server_ipV6->close();

    qApp->exit();
}

