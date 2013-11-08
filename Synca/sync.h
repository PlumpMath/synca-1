// Copyright (c) 2013 Grigory Demchenko

#pragma once

#include <string>
#include <boost/asio.hpp>
#include "defs.h"

namespace sync {

void go(Handler);

// forward declaration
struct Acceptor;
struct Socket
{
    friend struct Acceptor;
    
    Socket();
    Socket(Socket&& s);
    
    // чтение данных фиксированного размера
    void read(Buffer&);
    
    // чтение данных не больше, чем указанный размер буфера
    void readSome(Buffer&);
    
    // чтение данных вплоть до строки until
    int readUntil(Buffer&, const Buffer& until);
    
    // запись данных фиксированного размера
    void write(const Buffer&);
    
    // закрытие сокета
    void close();

private:
    boost::asio::ip::tcp::socket socket;
};

struct Acceptor
{
    // слушать порт для принятия соединений
    explicit Acceptor(int port);
    
    // создание сокета на новое соединение
    void accept(Socket& socket);

private:
    boost::asio::ip::tcp::acceptor acceptor;
};

}
