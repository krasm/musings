
#include <iostream>
#include <cassert>
#include <cstring>

namespace {
    int32_t max(int32_t l, int32_t r) {
        return (l > r) ? l : r;
    }
    int32_t min(int32_t l, int32_t r) {
        return (l < r) ? l : r;
    }
};

template<int BASE>
class number_t {
    bool negative;
    int8_t * digits;
    int32_t start;
    int32_t end;

public:
    number_t(const char * digits_, int32_t n)
        : negative(false), start(0), end(n-1)
    {
        assert(end >= 0);
        digits = new int8_t[n];
        for(int32_t i = start; i <= end; i++) {
            // no error checking - assuming that all input is correct
            if(digits_[i] <= '9')
                digits[i] = digits_[i] - '0';
            else
                digits[i] = 10 + (digits_[i] - 'A');
            assert(digits[i] >= 0 and digits[i] < BASE);
        }
    }

    number_t(int32_t n)
        : negative(false), start(0), end(n-1)
    {
        digits = new int8_t[n];
        for(int32_t i = end; i >= start; i--)
            digits[i] = 0;
    }

    number_t(const number_t & other)
        : negative(other.negative), start(0), end(other.size()-1)
    {
        digits = new int8_t[other.size()];
        for(int32_t i = 0; i < size(); i++) {
            digits[i] = other.digits[i];
        }
    }

    ~number_t() {
        delete [] digits;
    }

    number_t & operator=(const number_t & other) {
        if(this != &other) {
            delete [] digits;
            digits = new int8_t[other.size()];
            start = 0;
            end = other.size() - 1;
            for(int32_t i = other.start, j = 0; j <= end; i++, j++) {
                digits[j] = other.digits[i];
            }
        }
        return *this;
    }

    // 9's complement
    number_t complement(int32_t s = 0) const {
        number_t result(max(size(), s));
        // 1st take the 9's complement
        int32_t j = result.end;
        for(int32_t i = end; i >= start; i--, j--) {
            result.digits[j] = (BASE - 1) - digits[i];
        }
        // fill with 9s (i.e. BASE - 1)
        while(j >= 0) {
            result.digits[j--] = BASE - 1;
        }
        return result;
    }

    int32_t size() const {
        return end - start + 1;
    }

    bool is_negative() const {
        return negative;
    }

    void print_to(char * out) {
        int j = 0;
        if(is_negative()) {
            out[j++] = '-';
        }
        for(int i = 0; i < size(); i++) {
            out[j++] = to_printable(digits[start+i]);
        }
    }

    number_t multByPowerOfBase(int n) const {
        number_t result(size() + n);
        for(int32_t i = 0; i < size(); i++) 
            result.digits[result.start + i] = digits[start+i];

        return result;
    }

    number_t upperHalf(int32_t m) const {
        if(size() < m) 
            return number_t(0);

        number_t result(size() - m);
        for(int32_t i = result.end, j = end - m; i >= result.start; i--, j--) {
            result.digits[i] = digits[j];
        }

        return result;
    }

    number_t lowerHalf(int32_t m) const {
        if(size() < m)
            return *this;
        number_t result(m);
        for(int32_t i = result.end, j = end; i >= result.start; i--, j--) {
            result.digits[i] = digits[j];
        }
        return result;
    }

    friend number_t operator+(const number_t & lhs, const number_t & rhs) {
        int32_t n = max(lhs.size(), rhs.size());
        number_t result(n+1);
        bool carry = false;

        int32_t k = result.end;
        int32_t i = lhs.end;
        int32_t j = rhs.end;
        for(; i >= lhs.start and j >= rhs.start; i--, j--) {
            int8_t tmp = (carry ? 1 : 0) + lhs.digits[i] + rhs.digits[j];
            carry = (tmp / BASE) > 0;
            tmp = tmp % BASE;
            result.digits[k--] = tmp;
        }
        for(; i >= lhs.start; i--) {
            int8_t tmp = (carry ? 1 : 0) + lhs.digits[i];
            carry = (tmp / BASE) == 1;
            tmp = tmp % BASE;
            result.digits[k--] = tmp;
        }
        for(; j >= rhs.start; j--) {
            int8_t tmp = (carry ? 1 : 0) + rhs.digits[j];
            carry = (tmp / BASE) == 1;
            tmp = tmp % BASE;
            result.digits[k--] = tmp;
        }

        result.digits[0] = (carry ? 1 : 0);
        result.start = (carry ? 0 : 1);

        return result;
    }

    friend number_t operator-(const number_t & lhs, const number_t & rhs) {
        int32_t n = max(lhs.size(), rhs.size());
        number_t result = lhs + rhs.complement(n);

        if(result.digits[0] == 1) {
            bool carry = true;
            for(int32_t i = result.end; i > 0; i--) {
                int8_t t = (result.digits[i] + (carry ? 1 : 0));
                carry = t >= BASE;
                result.digits[i] = t % BASE;
            }
            assert(carry == false);
        } else {
            for(int32_t i = result.end; i > 0; i--) {
                result.digits[i] = (BASE - 1) - result.digits[i];
            }
            result.negative = true;
        }
        result.digits[0] = 0;
        result.start = 1;
        return result;
    }

    friend bool operator<(const number_t & lhs, const number_t & rhs) {
        if(lhs.size() == rhs.size()) {
            for(int32_t i = lhs.start, j = rhs.start; i <= lhs.end and j <= rhs.end; i++, j++) {
                if(lhs.digits[i] == rhs.digits[j])
                    continue;
                return lhs.digits[i] < rhs.digits[j];
            }
        }

        return lhs.size() < rhs.size();
    }

    friend bool operator==(const number_t & lhs, const number_t & rhs) {
        if(lhs.size() == rhs.size()) {
            for(int32_t i = lhs.start, j = rhs.start; i <= lhs.end and j <= rhs.end; i++, j++) {
                if(lhs.digits[i] != rhs.digits[j])
                    return false;
            }
            return true;
        }

        return false;
    }

    friend number_t operator*(const number_t & lhs, const number_t & rhs) {
        if(lhs.size() == 1) {
            return mult(lhs, rhs);
        } else if(rhs.size() == 1) {
            return mult(rhs, lhs);
        } else {
            int32_t m = min(lhs.size(), rhs.size());
            int32_t m2 = m / 2;

            number_t a = lhs.upperHalf(m2);
            number_t b = lhs.lowerHalf(m2);
            number_t c = rhs.upperHalf(m2);
            number_t d = rhs.lowerHalf(m2);

            number_t z0 = b * d;
            number_t z1 = (a+b) * (c+d);
            number_t z2 = a * c;

            return z2.multByPowerOfBase(2 * m2) + (z1-z2-z0).multByPowerOfBase(m2) + z0;
        }
    }

    static number_t mult(const number_t & single, const number_t & rhs) {
        number_t result(rhs.size() + 1);
        int32_t carry = 0;

        for(int32_t i = rhs.end, j = result.end; i >= rhs.start; i--, j--) {
            int32_t t = rhs.digits[i] * single.digits[single.end];
            result.digits[j] = (t + carry) % BASE;
            carry = (t + carry) / BASE;
        }
        result.digits[0] = carry;
        if(carry == 0)
            result.start = 1;
        // TODO check signs
        result.negative = not ((not single.negative and not rhs.negative)
            or (single.negative and rhs.negative));

        return result;
    }

    static char to_printable(int8_t d) {
        if(d < 10) {
            return (char)('0' + d);
        } else{
            return (char)('A' + (d - 10));
        }
    }

    friend std::ostream & operator<<(std::ostream & out, const number_t & num) {
        if(num.negative) {
            out << "-";
        }
        for(int32_t i = num.start; i <= num.end; i++) {
            out << to_printable(num.digits[i]);
        }

        return out;
    }
};

