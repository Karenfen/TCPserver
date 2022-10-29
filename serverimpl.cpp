#include "serverimpl.h"

#include <iostream>
#include <QAbstractSocket>
#include <exception>
#include <QApplication>




servImpl::servImpl(const int& port, QObject* parent):
    QObject(parent), server_(new QTcpServer()), server_ipV6(new QTcpServer()), port_(port)
{
    if(!(server_ && server_ipV6))
    {
        throw std::runtime_error("Initialization error!");
    }

    connect(server_.get(), &QTcpServer::acceptError, this, &servImpl::accept_error_handler);
    connect(server_ipV6.get(), &QTcpServer::acceptError, this, &servImpl::accept_error_handler);
    connect(server_.get(), &QTcpServer::newConnection, this, &servImpl::accept_connection);
    connect(server_ipV6.get(), &QTcpServer::newConnection, this, &servImpl::accept_connection);
}


void servImpl::run()
{
    if(!server_->listen(QHostAddress::LocalHost, port_))
        std::cerr << "Listening server ip v4 error!" << std::endl;

    if(!server_ipV6->listen(QHostAddress::LocalHostIPv6, port_))
        std::cerr << "Listening server ip v6 error!" << std::endl;

    if(!(server_->isListening() && server_ipV6->isListening()))
        throw std::logic_error(server_->errorString().toStdString() + " / " + server_ipV6->errorString().toStdString());

    std::cout << "Server IP4 is listening address ("
              <<  server_->serverAddress().toString().toStdString()
              << ") port: " << server_->serverPort() << std::endl;

    std::cout << "Server IP6 is listening address ("
              <<  server_ipV6->serverAddress().toString().toStdString()
              << ") port: " << server_ipV6->serverPort() << std::endl;
    std::cout << "========================================================" << std::endl;
}


void servImpl::accept_connection()
{
    auto klient_socket = qobject_cast<QTcpServer*>(sender())->nextPendingConnection();

    if(klient_socket)
    {
        auto klient = new TCPconnection(klient_socket, this);

        if(klient)
        {
            std::cout << "New client connected (" << klient->get_info() << ")" << std::endl;

            connect(klient, &TCPconnection::connection_disconnected, this, &servImpl::delet_klient);
            connect(klient, &TCPconnection::close_server, this, &servImpl::shutdown);
        }
    }
}


void servImpl::accept_error_handler(QAbstractSocket::SocketError socket_error)
{
    std::cerr << "Accept error! " << socket_error << std::endl;
    qobject_cast<QTcpServer>(sender()).resumeAccepting();
}


void servImpl::delet_klient(TCPconnection *klient)
{
    if(!klient)
        return;

    std::cout << "Connection with client (" << klient->get_info() << ") aborted!" << std::endl;

    klient->deleteLater();
}


void servImpl::shutdown()
{
    std::cout << "Server shuts down..." << std::endl;

    server_->close();
    server_ipV6->close();

    qApp->exit();
}

