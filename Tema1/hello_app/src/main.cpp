#include <hello/hello.h>   // header exported by hello_lib

#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Application hello_app, using hello_lib v"
              << hello::libVersion() << std::endl << std::endl;

    hello::Hello hello{argc > 1 ? argv[1] : "world"};

    hello.start();

    hello.run();

    hello.stop();

    return 0;
}
