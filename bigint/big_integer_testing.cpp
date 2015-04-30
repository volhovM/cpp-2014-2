#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest/gtest.h>

#include "big_integer.h"

using namespace std;

//TEST(correctness, my_vector_test){
////    my_vector vect = my_vector();
////    for (size_t i = 0; i < 1000; i++){
////        vect.push_back(i);
////    }
////    my_vector v2 = vect;
////    for (size_t i = 0; i < 1000; i += 12) {
////        EXPECT_EQ(v2[i], i);
////        v2[i] = i * 2;
////    }
////    v2[3] = 555;
////    for (size_t i = 0; i < 1000; i += 12) {
////        EXPECT_EQ(v2[i], i * 2);
////    }

////    EXPECT_EQ(v2[3], 555);
////    EXPECT_EQ(vect[3], 3);

//    my_vector vect2 = my_vector((size_t) 15);
//    vect2.dump_modep();
//    vect2[5] = 5;
//    vect2.dump_modep();
////     unsigned int a = vect2[14] + vect2[0] * vect2[5];
//    vect2[0] = 2;
//    vect2[14] = 3;
////     vect2[6] = 6;
//    vect2[6] = vect2[5] * vect2[0] + vect2[14];
//    vect2.dump_modep();
//    EXPECT_EQ(vect2[6], 5*2+3);
//    cout << "FdFSD" << endl;
//}

TEST(correctness, two_plus_two)
{
    EXPECT_EQ(big_integer(2) + big_integer(2), big_integer(4));
    EXPECT_EQ(big_integer(2) + 2             , 4); // implicit converion from int must work
    EXPECT_EQ(2              + big_integer(2), 4);
}

TEST(correctness, default_ctor)
{
    big_integer a;
    big_integer b = 0;
    EXPECT_EQ(a, 0);
    EXPECT_EQ(a, b);
}

TEST(correctness, copy_ctor)
{
    big_integer a = 3;
    big_integer b = a;

    EXPECT_EQ(a, b);
    EXPECT_EQ(b, 3);
}

TEST(correctness, copy_ctor_real_copy)
{
    big_integer a = 3;
    big_integer b = a;
    a = 5;

    EXPECT_EQ(b, 3);
}

TEST(correctness, copy_ctor_real_copy2)
{
    big_integer a = 3;
    big_integer b = a;
    b = 5;

    EXPECT_EQ(a, 3);
}

TEST(correctness, assignment_operator)
{
    big_integer a = 4;
    big_integer b = 7;
    b = a;

    EXPECT_TRUE(a == b);
}

TEST(correctness, self_assignment)
{
    big_integer a = 5;
    a = a;

    EXPECT_TRUE(a == 5);
}

TEST(correctness, assignment_return_value)
{
    big_integer a = 4;
    big_integer b = 7;
    (a = b) = a;

    EXPECT_TRUE(a == 7);
    EXPECT_TRUE(b == 7);
}

TEST(correctness, comparisons)
{
    big_integer a = 100;
    big_integer b = 100;
    big_integer c = 200;

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(big_integer(-125) < big_integer(0));
    EXPECT_TRUE(big_integer(3261) > big_integer(-1126));
    EXPECT_TRUE(big_integer(125) > big_integer(0));
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(c >= a);
}

TEST(correctness, compare_zero_and_minus_zero)
{
    big_integer a;
    big_integer b = -a;

    EXPECT_TRUE(a == b);
}

TEST(correctness, add)
{
    big_integer a = 5;
    big_integer b = 20;

    EXPECT_TRUE(a + b == 25);

    a += b;
    EXPECT_TRUE(a == 25);
}

TEST(correctness, add_signed)
{
    big_integer a = 5;
    big_integer b = -20;

    EXPECT_TRUE(a + b == -15);

    a += b;
    EXPECT_TRUE(a == -15);
}

TEST(correctness, add_return_value)
{
    big_integer a = 5;
    big_integer b = 1;

    (a += b) += b;
    EXPECT_EQ(a, 7);
}

TEST(correctness, sub)
{
    big_integer a = 20;
    big_integer b = 4;

    EXPECT_EQ(a - b, 16);

    a -= b;
    EXPECT_EQ(a, 16);
}

TEST(correctness, sub_signed)
{
    big_integer a = 5;
    big_integer b = 20;

    EXPECT_TRUE(a - b == -15);

    a -= b;
    EXPECT_TRUE(a == -15);

    a -= -100;
    EXPECT_TRUE(a == 85);
}

TEST(correctness, sub_return_value)
{
    big_integer a = 5;
    big_integer b = 1;

    (a -= b) -= b;
    EXPECT_EQ(a, 3);
}

TEST(correctness, mul)
{
    big_integer a = 429496728LL;
    big_integer b = 2684354560LL;

    EXPECT_TRUE(a * b == big_integer("1152921500311879680"));
//    EXPECT_EQ(to_string(a), "429496728");

//    a *= b;
//    EXPECT_TRUE(a == 20);
}



TEST(correctness, mul_signed)
{
    big_integer a = -5;
    big_integer b = 20;

    EXPECT_TRUE(a * b == -100);

    a *= b;
    EXPECT_TRUE(a == -100);
}

TEST(correctness, mul_return_value)
{
    big_integer a = 5;
    big_integer b = 2;

    (a *= b) *= b;
    EXPECT_EQ(a, 20);
}



//TEST(correctness, my_test_mul)
//{
//    big_integer adding ("-532345678765434343234567878654567890009876543345343431138198369251532555");
//    big_integer a ("143535837289549191123444444732");
//    big_integer b ("9964362547858399995213231");
//    for (int i = 0; i < 100; i++){
//        if (i % 3 == 1){
//            a *= adding;
//        } else b *= adding;
////        cout << to_string_alt(a * b) + " \n" + to_string_alt(b * a) << endl << endl;
//        EXPECT_TRUE(a * b == b * a);
//    }
//}

TEST(correctness, unary_plus)
{
    big_integer a = 123;
    big_integer b = +a;

    EXPECT_TRUE(a == b);

    // this code should not compile:
    // &+a;
}

TEST(correctness, negation)
{
    big_integer a = 666;
    big_integer b = -a;

    EXPECT_TRUE(b == -666);
}


TEST(correctness, and_simple)
{
    big_integer a = -1;
    big_integer b(-1);

    EXPECT_EQ((a & b), -1);
}

TEST(correctness, and_)
{
    big_integer a = 0x55;
    big_integer b = 0xaa;

    EXPECT_TRUE((a & b) == 0);
    EXPECT_TRUE((a & 0xcc) == 0x44);
    a &= b;
    EXPECT_TRUE(a == 0);
}

TEST(correctness, and_signed)
{
    big_integer a = 0x55;
    big_integer b = 0xaa;

    EXPECT_EQ((b & -1), 0xaa);
    EXPECT_TRUE((a & (0xaa - 256)) == 0);
    EXPECT_TRUE((a & (0xcc - 256)) == 0x44);
}

TEST(correctness, and_return_value)
{
    big_integer a = 7;

    (a &= 3) &= 6;
    EXPECT_EQ(a, 2);
}

TEST(correctness, or_)
{
    big_integer a = 0x55;
    big_integer b = 0xaa;

    EXPECT_TRUE((a | b) == 0xff);
    a |= b;
    EXPECT_TRUE(a == 0xff);
}

TEST(correctness, or_signed)
{
    big_integer a = 0x55;
    big_integer b = 0xaa;

    EXPECT_TRUE((a | (b - 256)) == -1);
}

TEST(correctness, or_return_value)
{
    big_integer a = 1;

    (a |= 2) |= 4;
    EXPECT_EQ(a, 7);
}

TEST(correctness, xor_)
{
    big_integer a = 0xaa;
    big_integer b = 0xcc;

    EXPECT_TRUE((a ^ b) == 0x66);
}

TEST(correctness, xor_signed)
{
    big_integer a = 0xaa;
    big_integer b = 0xcc;

    EXPECT_TRUE((a ^ (b - 256)) == (0x66 - 256));
}

TEST(correctness, xor_return_value)
{
    big_integer a = 1;

    (a ^= 2) ^= 1;
    EXPECT_EQ(a, 2);
}

TEST(correctness, not_)
{
    big_integer a = 0xaa;

    EXPECT_EQ(~a ,(-a - 1));
}

TEST(correctness, not_2)
{
    big_integer a(15);

    EXPECT_EQ(~a ,(-a - 1));
}


TEST(correctness, shl_)
{
    big_integer a = 23;

    EXPECT_TRUE((a << 5) == 23 * 32);

    a <<= 5;
    EXPECT_TRUE(a == 23 * 32);
}

TEST(correctness, shl_signed)
{
    big_integer a = -1234;

    EXPECT_EQ((a << 5), -1234 << 5);

    a <<= 5;
    EXPECT_TRUE(a == -1234 << 5);
}

TEST(correctness, shl_return_value)
{
    big_integer a = 1;

    (a <<= 2) <<= 1;
    EXPECT_EQ(a, 8);
}

TEST(correctness, shr_)
{
    big_integer a = 23;

    EXPECT_EQ(a >> 2, 5);

    a >>= 2;
    EXPECT_EQ(a, 5);
}


TEST(correctness, shr_signed)
{
    big_integer a = -1234;

    EXPECT_EQ(a >> 3, -155);

    a >>= 3;
    EXPECT_EQ(a, -155);
}

TEST(correctness, shr_signed_2)
{
    big_integer a = -1;

    EXPECT_EQ(a >> 16, -1 >> 16);
}


TEST(correctness, shr_return_value)
{
    big_integer a = 64;

    (a >>= 2) >>= 1;
    EXPECT_EQ(a, 8);
}


TEST(correctness, compare_longlong_string){
    big_integer a("4295");
    big_integer b( 4295LL);

    EXPECT_TRUE(a == b);
}


TEST(correctness, mul_longlong_string){
    big_integer a("1316134912");
    big_integer b(10LL);
    big_integer c("13161349120");

    EXPECT_EQ(a*b, c);
}

TEST(correctness, sum_with_shift){
    big_integer a(0);
    big_integer one(1);
    big_integer b("4294967295");

    EXPECT_EQ(a.add_with_shift(one, 1) - one, b);
}

TEST(correctness, add_long_simple)
{
     big_integer a("4294967296");
     big_integer b("5");
     big_integer c("4294967301");

     EXPECT_EQ(a + b, c);
}

TEST(correctness, add_long)
{
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c("10000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000");

    EXPECT_EQ(a + b, c);
}

TEST(correctness, add_long_signed)
{
    big_integer a("-100000000000000000");
    big_integer b( "100000000000000000");

    EXPECT_EQ(a + b, 0);
}

TEST(correctness, long_str_sign)
{
    big_integer a("-100000000000000000");
    big_integer b( "100000000000000000");

    EXPECT_EQ(a, -b);
}


TEST(correctness, add_long_signed2)
{
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c( "-999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

    EXPECT_EQ(a + b, c);
}

TEST(correctness, add_long_pow2)
{
    big_integer a( "18446744073709551616");
    big_integer b("-18446744073709551616");
    big_integer c( "36893488147419103232");

    EXPECT_EQ(a + a, c);
    EXPECT_EQ(b + c, a);
    EXPECT_EQ(c + b, a);
}


TEST(correctness, sub_long)
{
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c( "9999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

    EXPECT_EQ(a - b, c);
}

TEST(correctness, mul_long)
{
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                                        "00000000000000000000000000000000000000");

    EXPECT_EQ(a * b, c);
}

TEST(correctness, mul_long_2)
{
    big_integer a("9999999999999999999999999999999999999");
    big_integer b("99999999999999998764345654324565432345673");
    big_integer c("999999999999999987643456543245654323356730000000000001235654345675434567654327");

//    EXPECT_EQ(a * b , c);
    EXPECT_TRUE(big_integer("1575148161") * big_integer("203478489463671465552323532336136192")
                == big_integer("320508768481759985272917261236288956674342912"));
}


TEST(correctness, mul_long_signed)
{
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "100000000000000000000000000000000000000");
    big_integer c("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                                        "00000000000000000000000000000000000000");

    EXPECT_EQ(a * b, c);
}

TEST(correctness, mul_long_signed2)
{
    big_integer a("-1000000000000000000000");
    big_integer c("1000000000000000000000000000000000000000000");

    EXPECT_EQ((a * a).sign, 1);
//    big_integer d(2);
//    big_integer t(10);
//    d /= t;
//    EXPECT_EQ(d, 0);
}

TEST(correctness, mul_long_pow2)
{
    big_integer a("18446744073709551616");
    big_integer b("340282366920938463463374607431768211456");
    big_integer c("115792089237316195423570985008687907853269984665640564039457584007913129639936");

    EXPECT_TRUE(a * a == b);
    EXPECT_TRUE(b * b == c);
}


TEST(correctness, negation_long)
{
    big_integer a( "10000000000000000000000000000000000000000000000000000");
    big_integer c("-10000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(-a, c);
    EXPECT_EQ(a, -c);
}


TEST(correctness, div_)
{
    big_integer a = 20;
    big_integer b = 5;
    big_integer c = 20;

    EXPECT_EQ(a / b, 4);
    EXPECT_EQ(a % b, 0);

    a /= b;
    EXPECT_TRUE(a == 4);

    c %= b;
    EXPECT_TRUE(c == 0);
}

TEST(correctness, div_signed)
{
    big_integer a = 20;
    big_integer b = -5;

    EXPECT_TRUE(a / b == -4);
    EXPECT_TRUE(a % b == 0);
}

TEST(correctness, div_rounding)
{
    big_integer a = 23;
    big_integer b = 5;

    EXPECT_TRUE(a / b == 4);
    EXPECT_TRUE(a % b == 3);
}

TEST(correctness, div_rounding_negative)
{
    big_integer a = 23;
    big_integer b = -5;
    big_integer c = -23;
    big_integer d = 5;

    EXPECT_TRUE(a / b == -4);
    EXPECT_TRUE(c / d == -4);
    EXPECT_EQ(a % b, 3);
    EXPECT_TRUE(c % d == -3);
}

TEST(correctness, div_return_value)
{
    big_integer a = 100;
    big_integer b = 2;

    (a /= b) /= b;
    EXPECT_EQ(a, 25);
}


//TEST(correctness, string_conv_simple)
//{
//    EXPECT_EQ(to_string(big_integer("02684354560")), "2684354560");
//}


TEST(correctness, div_long_simple)
{
    big_integer a("500000000000000000000000000000000");
    big_integer b("1000000000000000000");

    big_integer res = a / b;
    big_integer true_res("500000000000000");
    if (res != true_res){
        cout << to_string_alt(res) + " \n!=\n" + to_string_alt(true_res) << endl;
    }
    EXPECT_TRUE(res == true_res);
}

TEST(correctness, string_conv)
{
    EXPECT_EQ(to_string(big_integer("100")), "100");
    EXPECT_EQ(to_string(big_integer("0100")), "100");
    EXPECT_EQ(to_string(big_integer("0")), "0");
    EXPECT_EQ(to_string(big_integer("-0")), "0");
    EXPECT_EQ(to_string(big_integer("-1000000000000000")), "-1000000000000000");
}

TEST(correctness, div_long_harder)
{
    big_integer a("6977950791219891234994359411842872133530809593618177016655550819801818478332066298454263759842763948516923847933965796778733452389418236948123694623486257351865401923847923856479581235123415802170289261376418436009799300888933965796778733452389418236948123694623486257351865401923847923856479581235123415802170289261376418436009799300888");
    big_integer b("12419339657967787334523342534643");
    big_integer c("959339657967170289261376418436009799300888");
    big_integer d("532856958327654278752384610235356279485162340239586248512343957169654323456787654345676545654567876549339657967787334523894182369481236946234862573518654019238479238564795812351234158021702892613764184360097993008889339657967787334523894182369481236946234862573518654019238479238564795812351234158021702892613764184360097993008885456787654567");

    EXPECT_TRUE(a * b / b == a);
//    EXPECT_EQ(to_string(c * d), "511190812147478567913589628694684166533767648001643187881482924707798045706957347285606121696474351667544948106665826147919920060659420863711165225983189220651691994780538015460346034583983188423221374879837718024280952214972878775235048146276024521743229085225983189220651691994780538015460346034583983188423221374879837718024277227223494663100143468520859518492266986761025840355496");
}


TEST(correctness, my_test_div)
{
    big_integer adding ("523524353463575648654875468465");
    big_integer a ("53254265749876");
    big_integer b ("3534624664234");
    big_integer c = 0;
    for (int i = 0; i <= 20; i++){
        if (i % 5 != 1){
            a *= adding;
        } else b *= adding;
        if (!(b * a / b == a && a * b / a == b)){
            cout << to_string(i) << endl;
            cout << to_string_alt(b * a / b) + " \n" + to_string_alt(a) << endl;
            cout << to_string_alt(a * b / a) + " \n" + to_string_alt(b) << endl << endl;
        }
        EXPECT_TRUE(b * a / b == a && a * b / a == b);
    }
}


TEST(correctness, div_long_simple_2)
{
    big_integer a("1254236");
    big_integer b("7241567876545678342");
    big_integer c("45933");
    big_integer d("53232513444448569");

    EXPECT_EQ(a * b / b , a);
    EXPECT_EQ(c * d / c, d);
}


TEST(correctness, div_long_uint_hacks)
{
    big_integer a("-340282366920938463463374607431768211456");
    big_integer b("4294967296");

    EXPECT_EQ(a / b , big_integer("-79228162514264337593543950336"));
}


TEST(correctness, div_long_signed)
{
    big_integer a("-10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                      "100000000000000000000000000000000000000");
    big_integer c("-100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(a / b, c);
}

TEST(correctness, div_long_signed2)
{
    big_integer a("-10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b(                                                     "-100000000000000000000000000000000000000");
    big_integer c( "100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(a / b, c);
}

namespace
{
    unsigned const number_of_iterations = 10;
    size_t const number_of_multipliers = 1000;

    int myrand()
    {
        int val = rand() - RAND_MAX / 2;
        if (val != 0)
            return val;
        else
            return 1;
    }
}

TEST(correctness, mul_div_randomized)
{
    for (unsigned itn = 0; itn != number_of_iterations; ++itn)
    {
        std::vector<int> multipliers;

        for (size_t i = 0; i != number_of_multipliers; ++i)
        multipliers.push_back(myrand());

        big_integer accumulator = 1;
        cout << "MUL PART" << endl;
        for (size_t i = 0; i != number_of_multipliers; ++i)
            accumulator *= multipliers[i];

        std::random_shuffle(multipliers.begin(), multipliers.end());
        cout << "DIVIDE PART" << endl;
        for (size_t i = 1; i != number_of_multipliers; ++i)
            accumulator /= multipliers[i];

        EXPECT_EQ(accumulator, multipliers[0]);
    }
}

namespace
{
    template <typename T>
    void erase_unordered(std::vector<T>& v, typename std::vector<T>::iterator pos)
    {
        std::swap(v.back(), *pos);
        v.pop_back();
    }

    template <typename T>
    T extract_random_element(std::vector<T>& v)
    {
        size_t index = rand() % v.size();
        T copy = v[index];
        erase_unordered(v, v.begin() + index);
        return copy;
    }

    template <typename T>
    void merge_two(std::vector<T>& v)
    {
        assert(v.size() >= 2);

        T a = extract_random_element(v);
        T b = extract_random_element(v);

        T ab = a * b;
        ASSERT_TRUE(ab / a == b);
        ASSERT_TRUE(ab / b == a);

        v.push_back(ab);
    }

    template <typename T>
    T merge_all(std::vector<T> v)
    {
        assert(!v.empty());

        while (v.size() >= 2)
            merge_two(v);

        return v[0];
    }
}

TEST(correctness, mul_merge_randomized)
{
    for (unsigned itn = 0; itn != number_of_iterations; ++itn)
    {
        std::vector<big_integer> x;
        for (size_t i = 0; i != number_of_multipliers; ++i)
            x.push_back(myrand());

        big_integer a = merge_all(x);
        big_integer b = merge_all(x);

        EXPECT_TRUE(a == b);
    }
}
