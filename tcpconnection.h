#pragma once


#include <QObject>
#include <QtNetwork>
#include <memory>
#include <functional>
#include <boost/asio.hpp>


#define SIZE_BUFFER 1024


using namespace boost::asio::ip;



class TCPconnection :  public QObject, std::enable_shared_from_this<TCPconnection>
{
    Q_OBJECT

public:
    typedef  std::shared_ptr<TCPconnection> smart_pointer;

    static smart_pointer create(boost::asio::io_context& context);
    void start();
    tcp::socket& socket(){ return m_socket; };
    ~TCPconnection() = default;
    s
private slots:


signals:


private:
    TCPconnection(boost::asio::io_context& context, QObject* parent = nullptr);
    void m_handle_write(const boost::system::error_code&, size_t bytes_transferred);
    void m_recive_data();
    void m_handle_read(const boost::system::error_code&, size_t bytes_recived);
    void m_send_data(const std::string& data);
    void m_some_working();

private:
    tcp::socket m_socket;
    char m_buffer_read[SIZE_BUFFER];
    char m_buffer_write[SIZE_BUFFER];
};


