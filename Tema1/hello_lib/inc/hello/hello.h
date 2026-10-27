#ifndef HELLO_H
#define HELLO_H

#include <string>

namespace hello {

///\brief Versiunea bibliotecii statice hello_lib
const char* libVersion();

///\brief Clasa exportata de biblioteca statica hello_lib
class Hello
{
public:
    explicit Hello(const std::string& name = "world");

    ~Hello() = default;

public:
    void start() const;

    void run() const;

    void stop() const;

private:
    std::string m_name;
};

} // namespace hello

#endif // HELLO_H
