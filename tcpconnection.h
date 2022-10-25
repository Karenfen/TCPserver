#pragma once


#include <QObject>
#include <QtNetwork>
#include <memory>
#include <functional>


#define SIZE_BUFFER 1024




class TCPconnection :  public QObject, std::enable_shared_from_this<TCPconnection>
{
    Q_OBJECT

public:
    typedef  std::shared_ptr<TCPconnection> smart_pointer;

    static smart_pointer create(QTcpSocket* socket);
    void start();
    QTcpSocket* socket(){ return socket_; };
    ~TCPconnection();

private slots:
    void reading_data();
    void request_processing(int bytes_recived);
    void send_data();

signals:
    void reading_completed(int bytes_recived);
    void answer_ready();
    void close_connection();
    void shutdown_server();

private:
    TCPconnection(QTcpSocket* socket, QObject* parent = nullptr);

private:
    QTcpSocket* socket_{};
    QByteArray buffer_to_read_{};
    QByteArray buffer_to_write_{};
};


