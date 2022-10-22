#pragma once

#include <memory>


//class servImpl;
#include "serverimpl.h"

class TCPserver
{
public:
    TCPserver(const int& port = 0);
    ~TCPserver() = default;
    TCPserver(const TCPserver& other) = delete;
    TCPserver(TCPserver&& other): m_impl(std::move(other.m_impl)){};
    TCPserver& operator=(TCPserver other) = delete;

public:
    void start();

private:
    std::unique_ptr<servImpl> m_impl{};

};


