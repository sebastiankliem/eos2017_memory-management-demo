#include "LinkedList.h"

#include <iostream>
#include "stdlib.h"

LinkedList::LinkedList() {
    LinkedList::_init(DEFAULT_BLOCK_SIZE);
}
LinkedList::LinkedList(int blockSizeKb) {
    LinkedList::_init(blockSizeKb);
}

void LinkedList::_init(int blockSizeKb) {
    _blockSizeKb = blockSizeKb;
    _head = NULL;
    _tail = NULL;
    _length = 0;
}

bool LinkedList::isEmpty() {
    return _head == NULL && _tail == NULL;
}

int LinkedList::getBlockSizeKb() {
    return _blockSizeKb;
}

int LinkedList::getLength() {
    return _length;
}

void LinkedList::print() {
    list_block *iterator = new list_block;
    iterator = _head;
    
    while (iterator != NULL) {
        std::cout << iterator->address << " ";
        iterator = iterator->next;
    }
    std::cout << std::endl;
}

list_block *LinkedList::getBlockAt(unsigned int position) {
    list_block *current = new list_block;
    current = _head;
    if (position > 0) {
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
    }    
    return current;
}

void LinkedList::addBlockStart(void *address) {
    list_block *newBlock = new list_block;
    newBlock->address = address;
    newBlock->next = NULL;
    if (_length == 0) {
        _head = newBlock;
        _tail = newBlock;
    }
    else {
        newBlock->next = _head;
        _head = newBlock;
    }
    _length++;
}

void LinkedList::addBlockEnd(void *address) {
    list_block *newBlock = new list_block;
    newBlock->address = address;
    newBlock->next = NULL;
    if (_length == 0) {
        _head = newBlock;
        _tail = newBlock;
    }
    else {
        list_block *secondLastBlock = getBlockAt((_length == 1) ? 0 : _length - 2);
        secondLastBlock->next = newBlock;
        _tail = newBlock;
    }
    _length++;
}

void LinkedList::addBlockAt(unsigned int position, void *address) {
    if (_length == 0 || position == 0) {
        addBlockStart(address);
    }
    else {
        list_block *newBlock = new list_block;
        newBlock->address = address;
        list_block *beforeBlock = new list_block;
        beforeBlock = getBlockAt(position - 1);
        newBlock->next = beforeBlock->next;
        beforeBlock->next = newBlock;
        _length++;
    }
}

void LinkedList::removeBlockStart() {
    removeBlockAt(0);
}

void LinkedList::removeBlockEnd() {
    removeBlockAt(_length - 1);
}

void LinkedList::removeBlockAt(unsigned int position) {
    if (_length != 0 && position < _length) {
        list_block *removeBlock = new list_block;
        removeBlock = getBlockAt(position);
        if (_length == 1) {
            _head = NULL;
            _tail = NULL;
        }
        // else if (position == 0) {
        //     removeBlockStart();
        // }
        else {
            if (position == 0) {
                _head = removeBlock->next;
            }
            else {
                list_block *blockBefore = new list_block;
                blockBefore = getBlockAt(position - 1);
                blockBefore->next = removeBlock->next;
                if (position == _length - 1) {
                    _tail = blockBefore;
                }
            }
        }
        delete removeBlock;
        _length--;
    }
}
