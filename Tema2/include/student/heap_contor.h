#ifndef HEAP_CONTOR_H
#define HEAP_CONTOR_H

// Simple counter: how many new[] blocks have not yet been released with delete[].
// It must be 0 at the end of the program; otherwise there is a memory leak.
namespace heap {

void alocat();
void eliberat();
int  blocuriNeeliberate();

} // namespace heap

#endif // HEAP_CONTOR_H
