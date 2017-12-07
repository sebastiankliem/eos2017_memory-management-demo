#include <iostream>
#include "BuddyAllocator.h"

using namespace std;

int main(int argc, char* argv[]) {
    BuddyAllocator ba;

    // read memory size in kB
    if (argc == 2) {
        int buddySize = atoi(argv[1]);
        ba = BuddyAllocator(buddySize);
    }
    else {
        cout << "Usage: buddy <MemorySizeKiloBytes>\n";
        return EXIT_SUCCESS;
    }
    
    cout << "BUDDY SYSTEM ALLOCATION\n";
    cout << "Memory size: " << ba.getSizeKb() << " kB\n";
    cout << "Min block size: " << BLOCK_MIN_SIZE_KB << " kB\n";
    cout << "Memory begins at: " << (void *)(ba.getMemoryPointer()) << "\n";

    return EXIT_SUCCESS;
}
