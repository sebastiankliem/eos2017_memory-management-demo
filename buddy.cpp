#include <iostream>
#include "BuddyAllocator.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: buddy <MemorySizeKiloBytes>\n";
        return EXIT_SUCCESS;
    }
    // read memory size in kB
    int buddySize = atoi(argv[1]);
    BuddyAllocator ba = BuddyAllocator(buddySize);
    
    cout << "BUDDY SYSTEM ALLOCATION\n";
    cout << "Memory size: " << ba.getSizeKb() << " kB" << endl;
    cout << "Min block size: " << BLOCK_MIN_SIZE_KB << " kB" << endl;
    cout << "Memory begins at: " << (void *)(ba.getMemoryPointer()) << endl;
    cout << "Memory status: " << endl;
    ba.dumpLists();
    cout << endl;
    
    cout << "request: " << 120 << endl;
    char *myblock = ba.allocate(120);
    cout << "start addres: " << (void *)myblock << endl;
    ba.dumpLists();
    cout << endl;
    
    cout << "request: " << 128 << endl;
    char *myblock2 = ba.allocate(128);
    cout << "start addres: " << (void *)myblock2 << endl;
    ba.dumpLists();
    cout << endl;
    
    cout << "request: " << 40 << endl;
    char *myblock3 = ba.allocate(40);
    cout << "start addres: " << (void *)myblock3 << endl;
    ba.dumpLists();
    cout << endl;
    
    cout << "request: " << 356 << endl;
    char *myblock4 = ba.allocate(356);
    cout << "start addres: " << (void *)myblock4<< endl;
    ba.dumpLists();
    cout << endl;
    
    cout << "request: " << 359 << endl;
    char *myblock5 = ba.allocate(359);
    cout << "start addres: " << (void *)myblock5<< endl;
    ba.dumpLists();
    cout << endl;

    return EXIT_SUCCESS;
}
