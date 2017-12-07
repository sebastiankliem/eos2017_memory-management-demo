#include "LinkedList.h"
#include "stdlib.h"

LinkedList::LinkedList() {
    LinkedList::_init(DEFAULT_BLOCK_SIZE);
}
LinkedList::LinkedList(int blockSize) {
    LinkedList::_init(blockSize);
}

void LinkedList::_init(int blockSize) {
    _blockSize = blockSize;
    _head = NULL;
    _tail = NULL;
}

bool LinkedList::isEmpty() {
    return _head == NULL && _tail == NULL;
}

int LinkedList::getBlockSize() {
    return _blockSize;
}

void LinkedList::addBlock(void *address) {
    block *newBlock = new block;
    newBlock->address = address;
    newBlock->next = NULL;
    if (_head == NULL) {
        _head = newBlock;
        _tail = newBlock;
    }
    else {
        _tail->next = newBlock;
        _tail = newBlock;
    }
}