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
    std::cout << (void *)(_blocks[_getListNo(getSizeKb())].getBlockAt(0)->address) << std::endl;
}

int BuddyAllocator::_getListsSize() {
    return _getListNo(getSizeKb()) + 1;
}

int BuddyAllocator::_getListNo(int sizeKb) {
    return log2(sizeKb) - log2(BLOCK_MIN_SIZE_KB);
}

unsigned long BuddyAllocator::getSize() {
    return _size;
}

unsigned long BuddyAllocator::getSizeKb() {
    return _size / 1000;
}

char *BuddyAllocator::getMemoryPointer() {
    return _memory;
}
