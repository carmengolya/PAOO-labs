#include <student/heap_contor.h>

namespace heap {

namespace {
int g_blocuri = 0;   // visible only in this file (module-level encapsulation)
}

void alocat()             { ++g_blocuri; }
void eliberat()           { --g_blocuri; }
int  blocuriNeeliberate() { return g_blocuri; }

} // namespace heap
