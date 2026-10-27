#ifndef HELLO_H
#define HELLO_H

#include <string>

namespace hello {

///\brief Version of the hello_lib static library
const char* libVersion();

///\brief Class exported by the hello_lib static library
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
