#include "big_integer.h"

#include <cstring>
#include <stdexcept>
#include <iostream>
#include <climits>
#include <math.h>
#include <sstream>

using namespace std;

big_integer::big_integer()
{
    v.push_back(0);
    sign = 0;
}

big_integer::big_integer(big_integer const& other)
{
    v = other.v;
    sign = other.sign;
}

big_integer::big_integer(long long a)
{
//    cout << "TEST_CONSTR_LONGLONG: " + to_string(a) << endl;
    if (a <= UINT32_MAX && a >= -((long long) UINT32_MAX)) {
//        cout << "TESTTEST" << endl;
        if (a > 0) {
            sign = 1;
            v.push_back((unsigned int) a);
        }
        else if (a < 0) {
            sign = -1;
            v.push_back((unsigned int) a);
        }
        else {
            sign = 0;
            v.push_back(0);
        }
    }
    else {
        if (a < 0) sign = -1;
        else if (a > 0) sign = 1;
        else sign = 0;
        a = abs(a);
//        cout << "DEBUG3" << endl;
//        cout << "DEBUG3.3: a is " + to_string(a) + " " + to_string(a % 4294967295) << endl;
        for (int i = 0; a > 0; i++){
            v.push_back(a % UINT2_32);
//            cout << "wrote " + to_string(a % UINT2_32) << endl;
            a /= UINT2_32;
        }
    }
//    cout << "GOT_TEST_CONSTR_LONGLONG: " + to_string_alt(*this) << endl;
}

big_integer::big_integer(unsigned long long a)
{
//    cout << "TEST_CONSTR_ULONGLONG: " + to_string(a) << endl;
    if (a <= UINT32_MAX) {
        if (a > 0) {
            sign = 1;
            v.push_back((unsigned int) a);
        } else {
            sign = 0;
            v.push_back(0);
        }
    }
    else {
        if (a > 0) sign = 1;
        else sign = 0;
//        cout << "DEBUG3" << endl;
//        cout << "DEBUG3.3: a is " + to_string(a) + " " + to_string(a % 4294967295) << endl;
        for (int i = 0; a > 0; i++){
            v.push_back(a % UINT2_32);
//            cout << "wrote " + to_string(a % UINT2_32) << endl;
            a /= UINT2_32;
        }
    }
//    cout << "GOT_TEST_CONSTR_ULONGLONG: " + to_string(*this) << endl;
}


big_integer::big_integer(int a)
{
    if (a > 0) {
        sign = 1;
        v.push_back(a);
    }
    else if (a < 0) {
        sign = -1;
        v.push_back(-a);
    }
    else {
        sign = 0;
        v.push_back(0);
    }
}

big_integer::big_integer(unsigned int a)
{
    if (a > 0) {
        sign = 1;
        v.push_back(a);
    }
    else {
        sign = 0;
        v.push_back(0);
    }
}

big_integer::big_integer(std::string const& str)
{
//    cout << endl << "TEST_CONSTR_STR: " + str << endl;
    int aftsign = 1;
    size_t position = 0;
    if (str[0] == '-') {
        aftsign = -1;
        position++;
    } else if (str[0] == '+'){
        aftsign = 1;
        position++;
    }
    if (str[position] == '0'){
        bool got = false;
        for (size_t i = position; i < str.length(); i++){
            if (str[i] != '0'){
                aftsign = 1;
                position = i;
                got = true;
                break;
            }
        }
        if (!got){
            sign = 0;
            v.push_back(0);
            return;
        }
    } else if (str[0] -'0' >= 0 && str[0] - '0' <= 9){
        aftsign = 1;
    }
    sign = 0;
    v.push_back(0);
    big_integer power(1);
    big_integer ten(10);
    for (size_t i = str.length(); i > position; i--){
        *this += power * big_integer(str[i - 1] - '0');
        power *= ten;
    }
    sign = aftsign;
//    cout << "GOT_CONST_FROM_STR " + str + ": " + to_string_alt(*this) << endl << endl;
}

big_integer::~big_integer(){
    v.clear();
    sign = 0;
}

big_integer& big_integer::operator=(big_integer const& other)
{
    v = other.v;
    sign = other.sign;
    return *this;
}

big_integer& big_integer::operator+=(big_integer const& rhs)
{
//    cout << "TEST_SUM: " + to_string(*this) + to_string(rhs) << endl;
    if (rhs.sign == 0){
        return *this;
    }
    if (sign == 0){
        *this = big_integer(rhs);
        return *this;
    }
    if (rhs.sign != sign){
        big_integer z =  (*this -= -rhs); //strange here FIXME
        *this = z;
        return *this;
    }
    *this = add_with_shift(rhs, 0);
//    cout << "GOT_TEST_SUM: " + to_string(*this) << endl;
    return *this;
}


big_integer& big_integer::add_with_shift(big_integer const &rhs, unsigned int shift){
//    cout << "TEST_SUM_SHIFT: " + to_string_alt(*this) +  to_string_alt(rhs) + " shift:" + to_string(shift) << endl;
    bool carry = false;
    size_t vsize = v.size();
    unsigned long long curr;
    for (size_t i = 0; i < vsize; i++){
        curr = (unsigned long long) v[i] + (unsigned long long) (i >= shift && i - shift < rhs.v.size() ? rhs.v[i - shift] : 0);
        if (carry){
            carry = false;
            curr++;
        }
        if (curr > UINT32_MAX){
            carry = true;
            v[i] = curr % UINT2_32;
        } else {
            v[i] = curr;
        }
    }

    size_t size2 = rhs.v.size();
    for (size_t i = vsize; i < shift + size2; i++){
        int z = i - shift;
        curr = (z >=0 && z < (int) rhs.v.size() ? rhs.v[z] : 0);   //FIXME
        if (carry){
            carry = false;
            curr++;
        }
        if (curr > UINT32_MAX){
            carry = true;
            v.push_back(curr % UINT2_32);
        } else {
            v.push_back(curr);
        }
    }
    if (carry) {
        this->v.push_back(1);
    }
    sign = max(this->sign, rhs.sign);
//    cout << "GOT_TEST_SUM_SHIFT: " + to_string_alt(*this) << endl;
    return *this;
}

void clear_useless_zeroes(big_integer &a){
    for (int i = a.v.size() - 1; i > 0; i--){
        if (a.v[i] == 0) a.v.pop_back();
        else break;
    }
    if (a.v.size() == 1 && a.v[0] == 0){
        a.sign = 0;
    }
}

void determine_sign(big_integer &a){
    if (a > 0){
        a.sign = 1;
    } else if (a < 0){
        a.sign = -1;
    } else if (a == 0){
        a.sign = 0;
    }
}

big_integer& big_integer::operator-=(big_integer const& rhs)
{
//    cout << "TEST_SUB: " + to_string(*this) +  to_string(rhs) << endl;
    if (sign == 0){
        v = rhs.v;
        sign = -rhs.sign;
        return *this;
    } else if (rhs.sign == 0){
        return *this;
    } else if (rhs.sign != sign){
        big_integer x = -rhs;
        return (*this += x);
    }

    big_integer a;
    big_integer b;
    bool reverse = false;
    if (greater_unsigned(rhs, *this)){//swap!
        a = rhs;
        b = *this;
        reverse = true;
    } else if (less_unsigned(rhs, *this)){ //it's ok
        a = *this;
        b = rhs;
    } else  {
        *this = big_integer(0);
        return *this;
    }
    bool carry = false;
    long long current;
    for (size_t i = 0; i < a.v.size(); i++){
         current = (long long) a.v[i] - (long long) (b.v.size() > i ? b.v[i] : 0);
        if (carry){
            carry = false;
            current--;
        }
        if (current < 0){
            a.v[i] = 0 + current; //uint - longlong
            carry = true;
        } else {
            a.v[i] = current;
        }
    }
    *this = a;
    clear_useless_zeroes(*this);
    if (reverse) {
        *this = -(*this);
    }
    if (*this == big_integer(0)) sign = 0;
//    cout << "GOT_TEST_SUB: " + to_string(*this) << endl;
    return *this;
}

big_integer& big_integer::mul_with_uint(unsigned int num){
//    cout << "MUL WITH INT " + to_string_alt(*this) + " " + to_string(num) << endl;
    unsigned int carry = 0;
    size_t sizev = v.size();
    unsigned long long current;
    for (size_t i = 0; i < sizev || carry != 0; i++){
        if (i == v.size()) v.push_back(0);
        current = carry + v[i] * 1LL * num;
        carry = current / UINT2_32;
        v[i] = current - carry * UINT2_32;
    }
    while (v.size() > 1 && v.back() == 0) v.pop_back();
//    cout << "MUL WITH INT GOT " + to_string_alt(*this) << endl;
    return *this;
}

//STABLE AND THE QUICKEST MUL
big_integer& big_integer::operator*=(big_integer const& rhs){
//    cout << "MULLING " + to_string_alt(*this) + " " + to_string_alt(rhs) << endl;
    if (rhs.v.size() == 1) {
        this->mul_with_uint(rhs.v[0]);
        sign = sign * rhs.sign;
        return *this;
    }
    size_t gsize = v.size() + rhs.v.size();
    my_vector c(gsize);
//    for (size_t i = 0; i < gsize; i++) c[i] = 0;
    size_t vsize = v.size();
    size_t rhssize = (int) rhs.v.size();
    unsigned long long curr;
    unsigned int carry;
    for (size_t i = 0; i < vsize; i++){
        carry = 0;
        for (size_t j = 0; j <  rhssize || carry != 0; j++){
            curr = c[i + j] + ((unsigned long long) v[i]) * (j < (rhs.v.size()) ? rhs.v[j] : 0) + carry;
            carry = curr / UINT2_32;
            c[i + j] = curr - ((unsigned long long) carry) * UINT2_32;
//            c[i + j] = curr % UINT2_32;
        }
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    this->v = c;
    this->sign = sign * rhs.sign;
    return *this;
}

////AVERAGE-SPEED STABLE WORKING MUL
//big_integer& big_integer::operator*=(big_integer const& rhs)
//{
//    int final_sign = sign * rhs.sign;
//    sign = 1;
//    big_integer c = 0;
//    big_integer rhs_copy = rhs;
//    size_t sizev = v.size();
//    for(size_t i = 0; i < sizev; i++){
//        rhs_copy = rhs;
//        rhs_copy.mul_with_uint(v[i]);
//        c.add_with_shift(rhs_copy, i);
//    }
//    *this = c;
//    sign = final_sign;
//    return *this;
//}

//WORKING MUL:
////////////////////////
//    big_integer ret = 0;
////    cout << "TEST_MUL: " + to_string_alt(*this) + to_string_alt(rhs) << endl;
//    int tempsign = sign * rhs.sign;
//    for (int i = 0; i < v.size(); i++){
//        big_integer temp = 0;
//        for (int j = 0; j < rhs.v.size(); j++){
//            big_integer tempr(rhs.v[j] * ((unsigned long long) 1) * v[i]);
//            temp.add_with_shift(tempr, j);
//        }
//        ret.add_with_shift(temp, i);
//    }
//    *this = ret;
//    sign = tempsign;
////    cout << "GOT_TEST_MUL: " + to_string_alt(*this) << endl;
//    return *this;
/////////////////////////


big_integer& big_integer::divide_on_uint(unsigned int b){
    unsigned long long carry = 0;
    unsigned long long curr;
    for (size_t i = v.size(); i > 0; i--){
        curr = (unsigned long long) v[i - 1] + ((unsigned long long) carry) * UINT2_32;
        v[i - 1] = curr / b;
        carry =  curr - ((unsigned long long) v[i - 1]) * b;
    }
    while (v.size() > 1 && v.back() == 0) v.pop_back();
    return *this;
}


big_integer& big_integer::operator/=(big_integer const& rhs)
{
//    cout << "DIVIDING: " + to_string_alt(*this) + "/ " + to_string_alt(rhs) << endl;
    //жосткие костыли
    if (rhs.v.size() == 1) {
        this->divide_on_uint(rhs.v[0]);
        sign = sign * rhs.sign;
        return *this;
    }
    if (greater_unsigned(rhs, *this)) {
        this->sign = 0;
        this->v.clear();
        this->v.push_back(0);
        return *this;
    }

    big_integer b = big_integer(rhs);
    int temp_sign = sign * rhs.sign;
    sign = 1;
    b.sign = 1;
//    normalizing
    while ((long long) b.v[b.v.size() - 1] * 2 < UINT2_32){
        b*= 2;
        *this *= 2;
    }
//    cout << "after normalisation: " + to_string_alt(*this) + " , " + to_string_alt(b) << endl;
    big_integer a = take_from_to(*this, v.size() - b.v.size(), v.size() - 1);
    vector<unsigned int> v_temp;
    big_integer currb;
    int curr_bit = v.size() - b.v.size() - 1;
    size_t asize;
    size_t bsize;
    while (curr_bit >= 0) {
        a.add_as_low_bit(v[curr_bit]);
        curr_bit--;
        while (curr_bit >= 0 && a.v.size() < b.v.size() + 1){
            a.add_as_low_bit(v[curr_bit]);
            curr_bit--;
        }
        asize = a.v.size();
        bsize = b.v.size();
//        cout << "Current a & b are: " + to_string_alt(a) + " , " + to_string_alt(b) << endl;
//        cout << "pointer at " + to_string(curr_bit) << endl;
        if (asize <= bsize){
            if (asize < bsize){ // a / b, a < b
                cout << "a.size < b.size, break" << endl;
                break;
            }
            if (asize == 1 && a.v[0] < b.v[0]) { // ?? MAGIC
                cout << "break 443" << endl;
                break;
            }
            unsigned long long qGuess =
                    ((unsigned long long) a.v[asize - 1] * UINT2_32 + (asize > 1 ? (unsigned long long) a.v[asize - 1] : 0))
                    /
                    ((unsigned long long) b.v[bsize - 1] * UINT2_32 + (bsize > 1 ? (unsigned long long) b.v[bsize - 1] : 0));
            if (qGuess == 0) break;
            cout << "qguess1: " + to_string(qGuess) << endl;
            currb = big_integer(qGuess) * b;
            for (unsigned long long i = qGuess; i >= 0; i--){
                if (less_unsigned(currb, a)){ //guessed
                    if (i > UINT32_MAX){
                        v_temp.push_back(i / UINT2_32);
                        v_temp.push_back(i % UINT2_32);
                    } else v_temp.push_back((unsigned int) i);
                    break;
                }
                currb -= b;
            }
        } else if (asize > bsize){
            if (asize - 1 != bsize) {
                cout << "FATAL DIV ERROR! l(a - 1) != l(b)" << endl;
                break;
            }
            unsigned long long qGuess =
                    ((unsigned long long) a.v[asize - 1] * UINT2_32 + (unsigned long long) a.v[asize - 2])
                    /
                    ((unsigned long long) b.v[bsize - 1]);
            currb = big_integer(qGuess) * b;
            for (unsigned long long i = qGuess; i >= 0; i--){
                if (currb <= a){ //guessed
                    if (i > UINT32_MAX){
                        v_temp.push_back(i / UINT2_32);
                        v_temp.push_back(i % UINT2_32);
                    } else v_temp.push_back((unsigned int) i);
                    a -= currb;
                    break;
                }
                currb -= b;
            }
        } else {
            cout << "                    NOT GOOD!!!!!" << endl;
            break;
        }
        if (a == 0){
            while (curr_bit >= 0 && v[curr_bit] == 0){
                v_temp.push_back(0);
                curr_bit--;
            }
        }
    }
    v.clear();
    while (!v_temp.empty()) {
        v.push_back(v_temp[v_temp.size() - 1]);
        v_temp.pop_back();
    }
    sign = temp_sign;
//    cout << "DIVIDED, GOT : " + to_string_alt(*this) << endl;
    return *this;
}

big_integer take_from_to(big_integer const& rhs, unsigned int from, unsigned int to){
    big_integer b = big_integer(0);
    b.v.clear();
    for (size_t i = from; i <= to; i++){
        b.v.push_back(rhs.v[i]);
    }
    b.sign = rhs.sign;
    return b;
}

void big_integer::add_as_low_bit(unsigned int b){
//    cout << "adding to " + to_string_alt(*this) + " as low bit " + to_string(b) << endl;
    if (v.size() != 1 || v[0] != 0){ //shift all cells => 1
        v.push_back(v[v.size() - 1]);
        for (size_t i = v.size() - 1; i > 0; i--){
            v[i] = v[i - 1];
        }
    }
    v[0] = b;
//    cout << "got: " + to_string_alt(*this) << endl;
}

big_integer& big_integer::operator%=(big_integer const& rhs)
{   
    int signc = sign;
    sign = 1;
    big_integer c = (*this / rhs) * rhs;
    c.sign = 1;
//    cout << "C is " + to_string(c) << endl;
//    cout << "this is " + to_string(*this) << endl;
    *this -= c;
    if (sign != 0) {
        if (signc == 1 && rhs.sign == -1) sign = 1;
        else sign = signc * rhs.sign;
    }
    return *this;
}

void big_integer::invert()
{
    for (size_t i = 0; i < v.size(); i++) v[i] = ~v[i];
}

void big_integer::complement()
{
    if (sign < 0){
        sign = 1;
        invert();
        *this += 1;
    }
}

void big_integer::uncomplement()
{
    if (2 * (long long) v[v.size() - 1] >= UINT_MAX){
        *this -= 1;
        invert();
        sign = -1;
    }
}


big_integer& big_integer::operator&=(big_integer const& rhs)
{
//    cout << "TEST ANDING: " + to_string(*this) + " & " + to_string(rhs)<< endl;
    big_integer b(rhs);
    complement();
    b.complement();
    line_up_to(b);
    for (size_t i = 0; i < v.size(); i++){
        v[i] = v[i] & b.v[i];
    }
    uncomplement();
    clear_useless_zeroes(*this);
//    cout << "TEST ANDING GOT: " + to_string(*this) << endl;
    return *this;
}

big_integer& big_integer::operator|=(big_integer const& rhs)
{
    big_integer b(rhs);
    complement();
    b.complement();
    line_up_to(b);
    for (size_t i = 0; i < v.size(); i++){
        v[i] = v[i] | b.v[i];
    }
    uncomplement();
    clear_useless_zeroes(*this);
    return *this;
}

big_integer& big_integer::operator^=(big_integer const& rhs)
{
    big_integer b(rhs);
    complement();
    b.complement();
    line_up_to(b);
    for (size_t i = 0; i < v.size(); i++){
        v[i] = v[i] ^ b.v[i];
    }
    uncomplement();
    clear_useless_zeroes(*this);
    return *this;
}

big_integer& big_integer::operator<<=(int rhs)
{
    complement();
    for (int i = v.size() - 1; i >=0 ; i--){
        v[i] = v[i] << rhs;
//        uint adding =
    }
    uncomplement();
    clear_useless_zeroes(*this);
    return *this;
}

big_integer& big_integer::operator>>=(int rhs)
{
    bool isnegative = (sign < 0);
    complement();
    for (size_t i = 0; i < v.size() ; i++){
        v[i] = v[i] >> rhs;
        uint adding = (i + 1 < v.size()) ? (big_integer(*this).v[i+1] &
                                           ((1 << rhs) - 1)) : (isnegative ? UINT32_MAX ^ ((1 << (32 - rhs)) - 1) : 0);
        v[i] += adding;
    }
    uncomplement();
    clear_useless_zeroes(*this);
    return *this;
}

big_integer big_integer::operator+() const
{
    return *this;
}

///////////////////////

big_integer big_integer::operator~() const
{
    big_integer res = *this; //FIXME will spoil this
    res.complement();
    for (size_t i = 0; i < res.v.size(); i++)
    {
        res.v[i] = ~res.v[i];
    }
    res.uncomplement();
    return res;
}
/// ///////////////////


big_integer big_integer::operator-() const
{
    big_integer r(*this);
    r.sign = -r.sign;
    return (r);
}

big_integer& big_integer::operator++()
{
    return (*this += big_integer(1));
}

big_integer big_integer::operator++(int)
{
    big_integer r = *this;
    ++*this;
    return r;
}

void big_integer::line_up_to(big_integer &rhs){
    while (rhs.v.size() > v.size()){
        v.push_back(0);
    }
    while (v.size() > rhs.v.size()){
        rhs.v.push_back(0);
    }
}

big_integer& big_integer::operator--()
{
    return (*this -= big_integer(1));
}

big_integer big_integer::operator--(int)
{
    big_integer r = *this;
    --*this;
    return r;
}

big_integer operator+(big_integer a, big_integer const& b)
{
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b)
{
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b)
{
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const& b)
{
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const& b)
{
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const& b)
{
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const& b)
{
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const& b)
{
    return a ^= b;
}

big_integer operator<<(big_integer a, int b)
{
    return a <<= b;
}

big_integer operator>>(big_integer a, int b)
{
    return a >>= b;
}

bool operator==(big_integer const& a, big_integer const& b)
{
    if (a.sign == b.sign){
        if (a.v.size() != b.v.size()) return false;
        for (size_t i = 0; i < a.v.size(); i++){
            if (a.v[i] != b.v[i]) return false;
        }
        return true;
    }
    return false;
}

bool operator!=(big_integer const& a, big_integer const& b)
{
    return !(a == b);
}

bool operator<(big_integer const& a, big_integer const& b){
    if (a.sign < b.sign) return true;
    else if (a.sign > b.sign) return false;
    else return less_unsigned(a, b);
}

bool operator>(big_integer const& a, big_integer const& b){
    if (a.sign > b.sign) return true;
    else if (a.sign < b.sign) return false;
    else return greater_unsigned(a, b);
}

bool less_unsigned(big_integer const& a, big_integer const& b)
{
    if (a.v.size() < b.v.size()) return true;
    if (b.v.size() < a.v.size()) return false;
    for (int i = a.v.size() - 1; i >=0 ; i--){
        if (a.v[i] < b.v[i]) return true;
        if (a.v[i] > b.v[i]) return false;
    }
    return false;
}

bool greater_unsigned(big_integer const& a, big_integer const& b)
{
    if (a.v.size() > b.v.size()) return true;
    if (b.v.size() > a.v.size()) return false;
    for (int i = a.v.size() - 1; i >=0; i--){
        if (a.v[i] > b.v[i]) return true;
        if (a.v[i] < b.v[i]) return false;
    }
    return false;
}

bool operator<=(big_integer const& a, big_integer const& b)
{
    return (a < b) || (a == b);
}

bool operator>=(big_integer const& a, big_integer const& b)
{
    return (a > b) || (a == b);
}

std::string to_string(big_integer const& a)
{
    string res = "";
    big_integer x = a;
    bool neg = false;
//    cout << x.sign << endl;
    if (x == 0 || x.sign == 0) return "0";
    if (x.sign < 0) neg = true;
    while (greater_unsigned(x, 0)){
        unsigned int z = (x % 10).v[0];
//        cout << "z = " + to_string_alt(z) << endl;
//        cout << "x = " + to_string_alt(x) << endl;
        res = to_string(z) + res;
        x /= 10;
    }
//    cout << "res =    " + res << endl;
    if (neg) {
//        cout << "adding -" << endl;
        res = "-" + res;
    }
    return res;
}

std::string to_string_alt(big_integer const &a){
        string s = to_string(a.sign) + "::";
        for (size_t i = 0; i < a.v.size(); i++){
            s += "[" + to_string(a.v[i]) + "] ";
        }
        return s;
}

std::ostream& operator<<(std::ostream& s, big_integer const& a)
{
    return s << to_string(a);
}
