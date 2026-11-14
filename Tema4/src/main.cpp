#include <punct.h>

#include <iostream>

static void titlu(const char* text)
{
    std::cout << "\n==================== " << text << " ====================\n";
}

int main()
{
    std::cout << std::unitbuf;

    titlu("Item 10: operator= returneaza o referinta la *this");
    demoItem10();

    return 0;
}