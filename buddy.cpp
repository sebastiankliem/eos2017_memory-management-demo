#include <iostream>
#include "BuddyAllocator.h"

#define BUDDY_DEFAULT_SIZE 1024 * 1000 * sizeof(char) // 1024 KB
#define BLOCK_MIN_SIZE 64 * 1000 * sizeof(char) // 64 KB

using namespace std;

int main(int argc, char* argv[]) {
    int buddySize = BUDDY_DEFAULT_SIZE;
    BuddyAllocator ba = BuddyAllocator();

    // read memory size in kB
    if (argc == 2) {
        buddySize = atoi(argv[1]) * 1000 * sizeof(char);
    }
    
    cout << "BUDDY SYSTEM ALLOCATION\n";
    cout << "Memory size: " << buddySize / 1000 << " kB\n";
    cout << "Min block size: " << BLOCK_MIN_SIZE / 1000 << " kB\n";

    return 0;
}
