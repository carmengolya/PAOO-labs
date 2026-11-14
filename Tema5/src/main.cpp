#include <investitie.h>
#include <lock.h>

#include <iostream>

static void titlu(const char* text)
{
    std::cout << "\n==================== " << text << " ====================\n";
}

int main()
{
    std::cout << std::unitbuf;

    titlu("Item 13: foloseste obiecte pentru a gestiona resursele");
    demoItem13();

    titlu("Item 14: comportamentul la copiere al claselor RAII");
    demoItem14();

    return 0;
}