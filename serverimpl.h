#pragma once


#include <QObject>
#include <memory>

#include "tcpconnection.h"




class servImpl : public QObject
{
    Q_OBJECT

public:
    ~servImpl() = default;
    servImpl(const int& port, QObject* parent = nullptr);

protected:
    void start_accept();
    void run();

private slots:
    void handler(TCPconnection::smart_pointer klient, const boost::system::error_code &error);

signals:


private:
    std::string m_get_name_client(const tcp::socket& klient_sock);
    
private:
    QTcpServer server{};
    
    friend class TCPserver;
};

