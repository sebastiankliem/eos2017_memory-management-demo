#include "BuddyAllocator.h"
#include <iostream>
#include <math.h>
#include "stdlib.h"

BuddyAllocator::BuddyAllocator() {
    _init(MEMORY_DEFAULT_SIZE_KB);
}
BuddyAllocator::BuddyAllocator(int sizeKb) {
    _init(sizeKb);
}

void BuddyAllocator::_init(int sizeKb) {
    _size = sizeKb * 1000 * sizeof(char);
    _memory = (char *)malloc(_size);
    if (_memory == NULL) {
        std::cerr << "ERROR: could not allocate memory\n";
        exit(EXIT_SUCCESS);
    }

    _blocks = new LinkedList[_getListsSize()];
    for (int i = 0; i < _getListsSize(); i++) {
        _blocks[i] = LinkedList(pow(2, i + log2(BLOCK_MIN_SIZE_KB)));
    }
    _blocks[_getListNo(getSizeKb())].addBlockEnd(_memory);
}

int BuddyAllocator::_getListsSize() {
    return _getListNo(getSizeKb()) + 1;
}

int BuddyAllocator::_getListNo(int sizeKb) {
    return ceil(log2(sizeKb) - log2(BLOCK_MIN_SIZE_KB));
}

unsigned long BuddyAllocator::getSize() {
    return _size;
}

unsigned long BuddyAllocator::getSizeKb() {
    return _size / 1000;
}

void BuddyAllocator::_sortList(int listNo) {
    LinkedList unsorted = _blocks[listNo];
    LinkedList sorted = LinkedList(unsorted.getBlockSize());
    sorted.addBlockAt(0, unsorted.getBlockAt(0)->address);
    for (int i = 1; i < unsorted.getLength(); i++) {
        void *insertAddress = unsorted.getBlockAt(i)->address;
        for (int j = 0; j < sorted.getLength(); j++) {
            if (insertAddress <= (sorted.getBlockAt(j)->address)) {
                sorted.addBlockAt(0, insertAddress);
                break;
            }
            else if ( j == sorted.getLength() - 1 && insertAddress > (sorted.getBlockAt(j)->address)) {
                sorted.addBlockEnd(insertAddress);
            }
        }
    }

    _blocks[listNo] = sorted;
}

void BuddyAllocator::dumpLists() {
    for (int i = 0; i < _getListsSize(); i++) {
        std::cout << _blocks[i].getBlockSize() << ": ";
         _blocks[i].print();
    }
}

char *BuddyAllocator::getMemoryPointer() {
    return _memory;
}

buddy_block *BuddyAllocator::allocate(int sizeKb) {
    int listNo = _getListNo(sizeKb);
    bool found = false;
    block *allocateBlock = new block;
    while (!found) {
        if (_blocks[listNo].getLength() > 0) {
            allocateBlock = _blocks[listNo].getBlockAt(0);
            _blocks[listNo].removeBlockAt(0);
            found = true;
        }
        else if (listNo < _getListsSize()){
            listNo++;
            if (_blocks[listNo].getLength() > 0) {
                block *removeBlock = new block;
                removeBlock = _blocks[listNo].getBlockAt(0);
                _blocks[listNo - 1].addBlockAt(0, ((char *)removeBlock->address + (_blocks[listNo - 1].getBlockSize() * 1000)));
                _blocks[listNo - 1].addBlockAt(0, removeBlock->address);
                _blocks[listNo].removeBlockAt(0);
                listNo = _getListNo(sizeKb);
            }
        }
        else {
            break;
        }
    }
    if (found) {
        buddy_block *foundBlock = new buddy_block;
        foundBlock->startAddress = (char *) allocateBlock->address;
        foundBlock->sizeKb = _blocks[listNo].getBlockSize();
        return foundBlock;
    }
    else {
        return NULL;
    }
}
