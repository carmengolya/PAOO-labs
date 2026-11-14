#include <punct.h>
#include <fereastra.h>
#include <client.h>

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

    titlu("Item 11: auto-atribuirea in operator=");
    demoItem11();

    titlu("Item 12: copiaza toate partile unui obiect");
    demoItem12();

    return 0;
}