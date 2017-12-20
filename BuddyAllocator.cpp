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
    LinkedList sorted = LinkedList(unsorted.getBlockSizeKb());
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
                break;
            }
        }
    }

    _blocks[listNo] = sorted;
}

int *BuddyAllocator::_findBuddies(int listNo) {
    LinkedList list = _blocks[listNo];
    if (list.getLength() > 1) {
        int *buddies = (int *)malloc(sizeof(int) * 2);
        int blockSize = list.getBlockSizeKb() * 1000;
        for (int i = 0; i <= list.getLength() - 2; i++) {
            if (list.getBlockAt(i)->address == (char *)list.getBlockAt(i + 1)->address - blockSize) {
                buddies[0] = i;
                buddies[1] = i + 1;
                return buddies;
            }
        }        
    }
    return NULL;
}

void BuddyAllocator::_merge(int listNo) {
    int *buddies = _findBuddies(listNo);
    while (buddies != NULL) {
        void* startAddress = _blocks[listNo].getBlockAt(buddies[0])->address;
        _blocks[listNo].removeBlockAt(buddies[1]);
        _blocks[listNo].removeBlockAt(buddies[0]);
        _blocks[listNo + 1].addBlockAt(0, startAddress);
        _sortList(listNo + 1);

        buddies = _findBuddies(listNo);
    }
}

void BuddyAllocator::_mergeAll() {
    for (int i = 0; i < _getListsSize(); i++) {
        _merge(i);
    }
}

void BuddyAllocator::dumpLists() {
    for (int i = 0; i < _getListsSize(); i++) {
        std::cout << _blocks[i].getBlockSizeKb() << ": ";
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
                _blocks[listNo - 1].addBlockAt(0, ((char *)removeBlock->address + (_blocks[listNo - 1].getBlockSizeKb() * 1000)));
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
        foundBlock->sizeKb = _blocks[listNo].getBlockSizeKb();
        return foundBlock;
    }
    else {
        return NULL;
    }
}

void BuddyAllocator::deallocate(buddy_block *freeBlock) {
    int listNo = _getListNo(freeBlock->sizeKb);
    // _blocks[listNo].addBlockAt(0, freeBlock->startAddress);
    _blocks[listNo].addBlockEnd(freeBlock->startAddress);
    _sortList(listNo);
    _mergeAll();
}
