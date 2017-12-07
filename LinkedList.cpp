#include "LinkedList.h"

#include <iostream>
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
    _length = 0;
}

bool LinkedList::isEmpty() {
    return _head == NULL && _tail == NULL;
}

int LinkedList::getBlockSize() {
    return _blockSize;
}

int LinkedList::getLength() {
    return _length;
}

void LinkedList::print() {
    block *iterator = new block;
    iterator = _head;
    
    while (iterator != NULL) {
        std::cout << iterator->address << " ";
        iterator = iterator->next;
    }
    std::cout << std::endl;
}

void LinkedList::addBlockStart(void *address) {
    block *newBlock = new block;
    newBlock->address = address;
    newBlock->next = NULL;
    _length++;
    if (_head == NULL) {
        _head = newBlock;
        _tail = newBlock;
    }
    else {
        newBlock->next = _head->next;
        _head = newBlock;
    }
}

void LinkedList::addBlockEnd(void *address) {
    block *newBlock = new block;
    newBlock->address = address;
    newBlock->next = NULL;
    _length++;
    if (_head == NULL) {
        _head = newBlock;
        _tail = newBlock;
    }
    else {
        _tail->next = newBlock;
        _tail = newBlock;
    }
}
