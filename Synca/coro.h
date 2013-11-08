// Copyright (c) 2013 Grigory Demchenko

#pragma once

#include <functional>
#include <vector>
#include <boost/context/all.hpp>
#include "defs.h"

#define CLOG(D_msg)                 LOG(coro::isInsideCoro() << ": " << D_msg)

namespace coro {

// выход из сопрограммы
void yield();

// проверка того, что мы находимся внутри сопрограммы
bool isInsideCoro();

// сопрограмма
struct Coro
{
    // на всякий случай, мало ли
    friend void yield();
    
    Coro();
    
    // создание и запуск обработчика
    Coro(Handler);
    
    // без комментариев
    ~Coro();
    
    // запуск обработчика
    void start(Handler);

    // продолжение сопрограммы (только если она завершилась yield)
    void resume();
    
    // проверка того, что сопрограмму можно продолжить
    bool isStarted() const;

private:
    void init0();
    void yield0();
    void jump0(intptr_t p = 0);
    static void starterWrapper0(intptr_t p);
    void starter0(intptr_t p);

    bool started;
    bool running;

    boost::context::fcontext_t* context;
    boost::context::fcontext_t savedContext;
    std::vector<unsigned char> stack;
    std::exception_ptr exc;
};

}
