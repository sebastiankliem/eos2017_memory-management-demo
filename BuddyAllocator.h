#include "LinkedList.h"

#ifndef BuddyAllocator_h
#define BuddyAllocator_h

#define MEMORY_DEFAULT_SIZE_KB 1024
#define BLOCK_MIN_SIZE_KB 64

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
        char *getMemoryPointer();
};

#endif
