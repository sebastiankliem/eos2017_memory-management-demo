#include "BuddyAllocator.h"
#include <iostream>

BuddyAllocator::BuddyAllocator() {
    _size = MEMORY_DEFAULT_SIZE_KB * 1000 * sizeof(char);
}
BuddyAllocator::BuddyAllocator(int sizeKb) {
    _size = sizeKb * 1000 * sizeof(char);
}

unsigned long BuddyAllocator::getSize() {
    return _size;
}

unsigned long BuddyAllocator::getSizeKb() {
    return _size / 1000;
}
