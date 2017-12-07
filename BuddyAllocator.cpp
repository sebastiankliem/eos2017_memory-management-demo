#include "BuddyAllocator.h"
#include <iostream>
#include "stdlib.h"

BuddyAllocator::BuddyAllocator() {
    init(MEMORY_DEFAULT_SIZE_KB);
}
BuddyAllocator::BuddyAllocator(int sizeKb) {
    init(sizeKb);
}

void BuddyAllocator::init(int sizeKb) {
    _size = sizeKb * 1000 * sizeof(char);
    _memory = malloc(_size);
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
