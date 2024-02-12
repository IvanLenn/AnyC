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

    bool IsInt() const;
    bool IsDouble() const;
    bool IsPtr() const;
    uint64_t ToInt() const;
    double ToDouble() const;
    void* ToPtr() const;

    void Data(void* x) const;
    void print() const;

    bool operator==(const Any& rhs);
    bool operator!=(const Any& rhs);
    bool operator<(const Any& rhs);
    bool operator>(const Any& rhs);
    bool operator<=(const Any& rhs);
    bool operator>=(const Any& rhs);
    Any operator+(const Any& rhs);
    Any operator-(const Any& rhs);
    Any operator*(const Any& rhs);
    Any operator/(const Any& rhs);

    
};