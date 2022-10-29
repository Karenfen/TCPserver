#pragma once


#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <memory>
#include <functional>


#define MAX_COMMAND_SIZE 10

enum COMMANDS {CLOSE_SERVER, CLOSE_CONNECTION};



class TCPconnection :  public QObject
{
    Q_OBJECT

public:
    TCPconnection(QTcpSocket* socket, QObject* parent = nullptr);
    ~TCPconnection();
    void start();
    std::string get_info();
    bool is_disconnected();
    void disconnect();

private slots:
    void reading_data();
    void request_processing(int bytes_recived);
    void send_data();
    void handling_disconect();

signals:
    void reading_completed(int bytes_recived);
    void answer_ready();
    void close_server();
    void connection_disconnected(TCPconnection* connection);

private:
    void do_command_(const std::string& command);

private:
    std::unique_ptr<QTcpSocket> socket_{};
    QByteArray buffer_to_read_{};
    QByteArray buffer_to_write_{};
    std::map<std::string, COMMANDS> commands_{};
};


