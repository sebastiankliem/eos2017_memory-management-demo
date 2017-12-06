#ifndef BuddyAllocator_h
#define BuddyAllocator_h

#define MEMORY_DEFAULT_SIZE_KB 1024
#define BLOCK_MIN_SIZE_KB 64

class BuddyAllocator {
    private:
        unsigned long _size;

    public:
        BuddyAllocator();
        BuddyAllocator(int sizeKb);
        unsigned long getSize();
        unsigned long getSizeKb();
};

#endif
