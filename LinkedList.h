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
        int _blockSizeKb;
        unsigned int _length;

        void _init(int blockSizeKb);

    public:
        LinkedList();
        LinkedList(int blockSize);
        bool isEmpty();
        int getBlockSizeKb();
        int getLength();
        void print();
        block *getBlockAt(unsigned int position);
        void addBlockStart(void *address);
        void addBlockEnd(void *address);
        void addBlockAt(unsigned int position, void *address);
        void removeBlockStart();
        void removeBlockEnd();
        void removeBlockAt(unsigned int position);
};

#endif
