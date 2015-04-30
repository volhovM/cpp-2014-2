#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <gmp.h>
#include <iosfwd>
#include <vector>
#include "my_vector.h"

struct big_integer
{
    unsigned long long UINT2_32 = 4294967296;
    big_integer();
    big_integer(big_integer const& other);
    big_integer(unsigned long long a);
    big_integer(long long a);
    big_integer(unsigned int a);
    big_integer(int a);
    explicit big_integer(std::string const& str);
    ~big_integer();

    big_integer& operator=(big_integer const& other);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& mul_with_uint(unsigned int);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& divide_on_uint(unsigned int);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);


    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    //helper methods
    big_integer& add_with_shift(big_integer const &rhs, unsigned int shift);
    void line_up_to(big_integer &rhs);

    friend big_integer take_from_to(big_integer const& rhs, unsigned int from, unsigned int to);
    void add_as_low_bit(unsigned int b);
    void invert();
    void complement();
    void uncomplement();

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool less_unsigned(big_integer const& a, big_integer const& b);
    friend bool greater_unsigned(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);

    friend std::string to_string(big_integer const& a);
    friend std::string to_string_alt(big_integer const& a);
//private:
    int sign;
//    std::vector<unsigned int> v;
    my_vector v;
};

big_integer take_from_to(big_integer const& rhs, unsigned int from, unsigned int to);

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool less_unsigned(big_integer const& a, big_integer const& b);
bool greater_unsigned(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::string to_string_alt(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif // BIG_INTEGER_H
