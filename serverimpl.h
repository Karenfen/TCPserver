#pragma once


#include <QObject>
#include <memory>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>

#include "tcpconnection.h"





class servImpl : public QObject
{
    Q_OBJECT

public:
    ~servImpl() = default;

protected:
    servImpl(const int& port, QObject* parent = nullptr);
    void run();
    friend class TCPserver;

private slots:
    void accept_connection();
    void accept_error_handler(QAbstractSocket::SocketError socket_error);
    void delet_klient(TCPconnection* klient);
    void shutdown();
    
private:
    std::unique_ptr<QTcpServer> server_{};
    std::unique_ptr<QTcpServer> server_ipV6{};
    const int port_{};

};

