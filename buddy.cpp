#include <iostream>
#include "BuddyAllocator.h"

using namespace std;

int main(int argc, char* argv[]) {
    int buddySize = MEMORY_DEFAULT_SIZE_KB;
    BuddyAllocator ba = BuddyAllocator();

    // read memory size in kB
    if (argc == 2) {
        buddySize = atoi(argv[1]) * 1000 * sizeof(char);
    }
    
    cout << "BUDDY SYSTEM ALLOCATION\n";
    cout << "Memory size: " << ba.getSizeKb() << " kB\n";
    cout << "Min block size: " << BLOCK_MIN_SIZE_KB << " kB\n";

    return 0;
}
