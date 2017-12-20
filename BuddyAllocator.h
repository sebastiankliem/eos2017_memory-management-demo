#include "LinkedList.h"

#ifndef BuddyAllocator_h
#define BuddyAllocator_h

#define MEMORY_DEFAULT_SIZE_KB 1024
#define BLOCK_MIN_SIZE_KB 64

struct buddy_block {
    char* startAddress;
    unsigned int size;
};

class BuddyAllocator {
    private:
        unsigned long _size;
        char *_memory;
        LinkedList *_blocks;

        void _init(int sizeKb);
        int _getListsSize();
        int _getListNo(int sizeKb);

    public:
        BuddyAllocator();
        BuddyAllocator(int sizeKb);
        unsigned long getSize();
        unsigned long getSizeKb();
        void dumpLists();
        char *getMemoryPointer();
        buddy_block *allocate(int sizeKb);
};

#endif
