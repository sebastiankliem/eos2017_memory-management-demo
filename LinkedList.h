#ifndef LinkedList_h
#define LinkedList_h

#define DEFAULT_BLOCK_SIZE 64

struct list_block {
    void *address;
    list_block *next;
};

class LinkedList {
    private:
        list_block *_head;
        list_block *_tail;
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
        list_block *getBlockAt(unsigned int position);
        void addBlockStart(void *address);
        void addBlockEnd(void *address);
        void addBlockAt(unsigned int position, void *address);
        void removeBlockStart();
        void removeBlockEnd();
        void removeBlockAt(unsigned int position);
};

#endif
