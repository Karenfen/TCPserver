#include "tcpconnection.h"

#include <iostream>
#include <string>





std::shared_ptr<TCPconnection> TCPconnection::create(QTcpSocket* socket)
{
    return smart_pointer(new TCPconnection(socket));
}


TCPconnection::TCPconnection(QTcpSocket* socket, QObject* parent):
    QObject(parent), socket_(socket)
{
    connect(socket_, &QTcpSocket::readyRead, this, &TCPconnection::reading_data);
    connect(this, SIGNAL(reading_completed(int)), this, SLOT(request_processing(int)));
    connect(this, &TCPconnection::answer_ready, this, &TCPconnection::send_data);

}



TCPconnection::~TCPconnection()
{
    delete socket_;
}


void TCPconnection::reading_data()
{
   buffer_to_read_ = socket_->readAll();

   emit reading_completed(buffer_to_read_.size());
}



void TCPconnection::request_processing(int bytes_recived)
{
    buffer_to_write_ = buffer_to_read_;

    emit answer_ready();
}

void TCPconnection::send_data()
{
    socket_->write(buffer_to_write_);
}



