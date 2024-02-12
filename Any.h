#include <cstdint>
#include <string>

class Any{
public:
    static uint64_t TAG_MASK;
    static uint64_t BIAS;
    static uint64_t INT_TAG;
    static uint64_t DOUBLE_MASK;
    static uint64_t DOUBLE_UP;
    static uint64_t DOUBLE_LW;
    static uint64_t PTR_TAG;
    uint64_t data;

    Any(uint64_t x);
    Any(double x);
    Any(void* x);

    bool IsInt();
    bool IsDouble();
    bool IsPtr();

    void Data(void* x);

    void print();
};