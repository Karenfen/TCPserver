#include "tcpconnection.h"

#include <iostream>
#include <string>
#include <QHostAddress>






TCPconnection::TCPconnection(QTcpSocket* socket, QObject* parent):
    QObject(parent), socket_(socket)
{
    socket_->setSocketOption(QAbstractSocket::LowDelayOption, 0);

    commands_["exit"] = CLOSE_CONNECTION;
    commands_["shutdown"] = CLOSE_SERVER;

    connect(socket_.get(), &QTcpSocket::readyRead, this, &TCPconnection::reading_data);
    connect(this, &TCPconnection::reading_completed, this, &TCPconnection::request_processing);
    connect(this, &TCPconnection::answer_ready, this, &TCPconnection::send_data);
    connect(socket_.get(), &QTcpSocket::disconnected, this, &TCPconnection::handling_disconect);
}


TCPconnection::~TCPconnection()
{
    socket_->abort();
}

std::string TCPconnection::get_info()
{
    std::string info { "name: " + socket_->peerName().toStdString() +
                ", address: " + socket_->peerAddress().toString().toStdString() +
                ", port: " +  std::to_string(socket_->peerPort())};
    return info;
}

bool TCPconnection::is_disconnected()
{
    return (socket_->state() == QAbstractSocket::UnconnectedState);
}


void TCPconnection::disconnect()
{
    socket_->disconnectFromHost();
}


void TCPconnection::reading_data()
{
    if(is_disconnected())
        return;

    std::cout << "Receiving a request from a client: " << get_info() << std::endl;

    buffer_to_read_ = socket_->readAll();

    emit reading_completed(buffer_to_read_.size());
}



void TCPconnection::request_processing(int bytes_recived)
{
    buffer_to_write_ = buffer_to_read_;

    do_command_(std::string(buffer_to_read_));

    emit answer_ready();
}


void TCPconnection::send_data()
{
    if(is_disconnected())
        return;

    std::cout << "Sending a response from the client: " << get_info() << std::endl;

    socket_->write(buffer_to_write_);
}


void TCPconnection::handling_disconect()
{
    emit connection_disconnected(this);
}

void TCPconnection::do_command_(const std::string &command)
{
    if(command.length() > MAX_COMMAND_SIZE)
        return;

    COMMANDS command_code;

    try
    {
        command_code = commands_.at(command);
    }
    catch (std::exception &e)
    {
        return;
    }

    switch (command_code)
    {
    case CLOSE_CONNECTION:
        socket_->close();
        break;
    case CLOSE_SERVER:
        socket_->abort();
        emit close_server();
        break;
    default:
        break;
    }
}



