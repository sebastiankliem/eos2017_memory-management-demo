#include "BuddyAllocator.h"
#include <iostream>
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
