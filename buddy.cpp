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
    // LinkedList ll = LinkedList();
    // int x = 5, y = 6, z = 7, zz = 8;
    // cout << "x:  " << &x << endl;
    // cout << "y:  " << &y << endl;
    // cout << "z:  " << &z << endl;
    // cout << "zz: " << &zz << endl;
    // ll.addBlockEnd(&x);
    // ll.addBlockEnd(&y);
    // ll.print();
    // cout << ll.getLength() << endl;
    // ll.addBlockAt(0, &z);
    // ll.print();
    // cout << ll.getLength() << endl;
    // ll.addBlockAt(1, &zz);
    // ll.print();
    // cout << ll.getLength() << endl;
    // ll.removeBlockAt(2);
    // ll.print();
    // cout << ll.getLength() << endl;
    // ll.removeBlockAt(2);
    // ll.print();
    // cout << ll.getLength() << endl;
    // ll.removeBlockAt(0);
    // ll.print();
    // cout << ll.getLength() << endl;
    

    
    
    cout << "BUDDY SYSTEM ALLOCATION\n";
    cout << "Memory size: " << ba.getSizeKb() << " kB" << endl;
    cout << "Min block size: " << BLOCK_MIN_SIZE_KB << " kB" << endl;
    cout << "Memory begins at: " << (void *)(ba.getMemoryPointer()) << endl;

    return EXIT_SUCCESS;
}
