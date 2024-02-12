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

bool Any::IsInt() const {
    return (Any::data & INT_TAG) == INT_TAG;
}

bool Any::IsDouble() const {
    uint64_t tmp = Any::data & DOUBLE_MASK;
    return tmp >= DOUBLE_LW && tmp <= DOUBLE_UP;
}

bool Any::IsPtr() const{
    return (Any::data & TAG_MASK) == PTR_TAG;
}

uint64_t Any::ToInt() const{
    return Any::data & (~INT_TAG);
}

double Any::ToDouble() const {
    uint64_t tmp = Any::data - BIAS;
    double origin;
    memcpy(&origin, &tmp, sizeof(double));
    return origin;
}

void* Any::ToPtr() const {
    return reinterpret_cast<void*>(Any::data);
}

// pass in a pointer and stores the "value" of wtvr type inside pointer
void Any::Data(void* x) const {
    if (Any::IsInt()) {
        *(uint64_t*)x = Any::ToInt();
        return;
    }
    if (Any::IsDouble()) {   
        *(double*)x = Any::ToDouble();
        return;
    }
    if (Any::IsPtr()) {
        *(void**)x = Any::ToPtr();
        return;
    }
}

void Any::print() const {
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

bool Any::operator==(const Any& rhs) {
    if (Any::IsInt() && rhs.IsInt()) {
        return Any::ToInt() == rhs.ToInt();
    }
    if (Any::IsDouble() && rhs.IsDouble()) {
        return Any::ToDouble() == rhs.ToDouble();
    }
    if (Any::IsPtr() && rhs.IsPtr()) {
        return Any::ToPtr() == rhs.ToPtr();
    }
    return false;
}
bool Any::operator!=(const Any& rhs) {return !(*this == rhs);}
bool Any::operator<(const Any& rhs) {
    if (Any::IsInt() && rhs.IsInt()) {
        return Any::ToInt() < rhs.ToInt();
    }
    if (Any::IsDouble() && rhs.IsDouble()) {
        return Any::ToDouble() < rhs.ToDouble();
    }
    if (Any::IsPtr() && rhs.IsPtr()) {
        return Any::ToPtr() < rhs.ToPtr();
    }
    return false;
}
bool Any::operator>(const Any& rhs) {return !(*this < rhs || *this == rhs);}
bool Any::operator<=(const Any& rhs) {return *this < rhs || *this == rhs;}
bool Any::operator>=(const Any& rhs) {return *this > rhs || *this == rhs;}
