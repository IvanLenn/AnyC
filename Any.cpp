#include "Any.h"
#include <cstring>
#include <string>
#include <cstdio>

uint64_t Any::TAG_MASK     = 0xFFFF000000000000uLL;
uint64_t Any::BIAS         =    0x1000000000000uLL;
uint64_t Any::INT_TAG      = 0xFFFC000000000000uLL;
uint64_t Any::DOUBLE_MASK  = 0x7FFF000000000000uLL;
uint64_t Any::DOUBLE_UP    = 0x7FF0000000000000uLL;
uint64_t Any::DOUBLE_LW    = 0x0001000000000000uLL;
uint64_t Any::PTR_TAG      = 0x0000000000000000uLL;

// only 50-bits unsigned int
Any::Any(uint64_t x) {
    Any::data = x | Any::INT_TAG;
}

// Add bias
Any::Any(double x) {
    memcpy(static_cast<void*>(&(Any::data)), &x, sizeof(double));
    Any::data += BIAS;
}

// high 16 bits all zero
Any::Any(void* x) {
    memcpy(static_cast<void*>(&(Any::data)), &x, sizeof(void*));
}

bool Any::IsInt() {
    return (Any::data & INT_TAG) == INT_TAG;
}

bool Any::IsDouble() {
    uint64_t tmp = Any::data & DOUBLE_MASK;
    return tmp >= DOUBLE_LW && tmp <= DOUBLE_UP;
}

bool Any::IsPtr() {
    return (Any::data & TAG_MASK) == PTR_TAG;
}

// pass in a pointer and stores the "value" of wtvr type inside pointer
void Any::Data(void* x) {
    if (Any::IsInt()) {
        *(uint64_t*)x = Any::data & (~INT_TAG);
        return;
    }
    if (Any::IsDouble()) {   
        uint64_t tmp = Any::data - BIAS;
        memcpy(x, &tmp, sizeof(double));
        return;
    }
    if (Any::IsPtr()) {
        *(uint64_t*)x = Any::data;
        return;
    }
}

void Any::print() {
    if (Any::IsInt()) {
        printf("Int: %llu\n", Any::data & (~INT_TAG));
        return;
    }
    if (Any::IsDouble()) {
        uint64_t tmp = Any::data - BIAS;
        double origin;
        memcpy(&origin, &tmp, sizeof(double));
        printf("Double: %f\n", origin);
        return;
    }
    if (Any::IsPtr()) {
        printf("Pointer address: %p\n", reinterpret_cast<void*>(Any::data));
        return;
    }
}
