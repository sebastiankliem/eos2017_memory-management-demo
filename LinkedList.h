#ifndef LinkedList_h
#define LinkedList_h

#define DEFAULT_BLOCK_SIZE 64

struct block {
    void *address;
    block *next;
};

class LinkedList {
    private:
        block *_head;
        block *_tail;
        int _blockSize;

        void _init(int blockSize);

    public:
        LinkedList();
        LinkedList(int blockSize);
        bool isEmpty();
        int getBlockSize();
        void addBlock(void *address);
};

#endif
