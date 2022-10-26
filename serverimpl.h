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
    servImpl(const int& port, QObject* parent = nullptr);

protected:
    void run();
    friend class TCPserver;

private slots:
    void accept_connection();
    void accept_error_handler(QAbstractSocket::SocketError socket_error);
    void delet_klient(TCPconnection* klient);
    void shutdown(TCPconnection* klient);

signals:
    void new_connection(std::shared_ptr<QTcpSocket> klient_socket);
    
private:
    std::unique_ptr<QTcpServer> server_ipV4{};
    std::unique_ptr<QTcpServer> server_ipV6{};
    const int port_{};

};

