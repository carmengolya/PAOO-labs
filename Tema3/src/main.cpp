#include <item4.h>
#include <item5.h>
#include <item6.h>

#include <iostream>

static void titlu(const char* text)
{
    std::cout << "\n==================== " << text << " ====================\n";
}

int main()
{
    std::cout << std::unitbuf;       // mesajele apar imediat pe ecran
    std::cout << "\n>>> main() a inceput (Jurnal-ul de mai sus a fost creat INAINTE)\n";

    titlu("Item 4: initializeaza obiectele inainte de folosire");
    demoItem4();

    titlu("Item 5: functiile scrise si apelate de compilator");
    demoItem5();

    titlu("Item 6: interzice functiile generate pe care nu le vrei");
    demoItem6();

    std::cout << "\n>>> main() s-a terminat\n";
    return 0;
}
