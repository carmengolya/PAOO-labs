#include <hello/hello.h>   // header public  (din inc/)
#include "hello_config.h"  // header privat (din src/)

#include <chrono>
#include <ctime>
#include <iostream>

namespace hello {

const char* libVersion()
{
    return HELLO_LIB_VERSION;
}

Hello::Hello(const std::string& name)
    : m_name(name)
{
    std::cout << "Library hello_lib (static)" << std::endl
              << "Version " << libVersion() << std::endl
              << COPYRIGHT_INFO << std::endl
              << std::endl;
}

void Hello::start() const
{
    std::cout << str_hello << m_name << "!" << std::endl << std::endl;
}

void Hello::run() const
{
    std::time_t crttime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << str_timeis << std::ctime(&crttime) << std::endl;
}

void Hello::stop() const
{
    std::cout << str_goodbye << m_name << "!" << std::endl;
}

} // namespace hello
