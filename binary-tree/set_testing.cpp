#include <algorithm>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest/gtest.h>
#include <vector>

#include "set.h"


TEST(correctness, firsttest){
    set::node* a = new set::node(1);
    set::node* b = new set::node(a);
    b->value = 3;
    b->r = new set::node(a);
    b->r->value = 999;
    a->l = b;
    a->dumpN();
    std::cout << std::endl;
//    delete b;
    delete a;
}


TEST(correctness, node_eql){
    set::node* a = new set::node(2);
    set::node* b = new set::node(2);
    a->l = new set::node(a, 5);
    b->l = new set::node(b, 5);
    EXPECT_TRUE(*a == *b);
    EXPECT_TRUE(a->get_size() == 2);
    delete a;
    delete b;
}

TEST(correctness, assignment){
    set a;
    for (size_t i = 0; i < 100; i++) a.insert(rand() % 100);
    set b;
    for (size_t i = 0; i < 50; i++) b.insert(rand() % 200);
    a = b;
    EXPECT_TRUE(a == b);
}


TEST(correctness, assignment2){
    set a;
    for (size_t i = 0; i < 100; i++) a.insert(rand() % 100);
    set b;
    for (size_t i = 0; i < 50; i++) b.insert(rand() % 200);
    b = a;
    EXPECT_TRUE(a == b);
}

TEST(correctness, begin){
    set a;
    set b = a;
    EXPECT_TRUE(a.begin() == b.begin());
}

TEST(correctness, end){
    set a;
    set b = a;
    EXPECT_TRUE(a.end() == b.end());
}

TEST(correctness, conversions){
    set::node* a = new set::node(5);
    a->l = new set::node(a, -300);
    a->r = new set::node(a, 6);
    a->l->r = new set::node(a->l, -228);
    set* s = new set(*a);
//    a.dumpN();
    EXPECT_TRUE(a->get_size() == 4);
    EXPECT_TRUE(s->size() == 5);
    EXPECT_TRUE(*(s->begin()) == -300);
//    s.dumpN();
    for (set::iterator j = s->find(-228); j != s->end(); j++){
        std::cout << std::to_string(*j) << std::endl;
    }
    for (set::iterator j = s->end(); j != s->begin(); j--){
        std::cout << std::to_string(*j) << std::endl;
    }
    delete s;
}

TEST(correctness, inserts_findings){
    std::vector<int> vec;
    set s;
    for (int i = 0; i < 40; i++){
        s.insert(rand() % 200);
    }
    for (set::iterator i = s.begin(); i != s.end(); i++){
        vec.push_back(*i);
        vec.push_back(*s.find(*i));
    }
    for (size_t i = 1; i < vec.size(); i++){
        EXPECT_TRUE(vec[i] >= vec[i - 1]);
    }
}

TEST(correctness, deletes) {
    set s;
    for (int i = 0; i < 100; i++) {
        s.insert(rand() % 600);
    }
    for (set::iterator i = s.begin(); i != s.end(); i++){
        if ((*i) % 3 == 0) {
            i = s.erase(i);
            i--;
        }
    }
    for (set::iterator i = s.begin(); i != s.end(); i++){
        EXPECT_TRUE(*i % 3 != 0);
        if (*i % 3 == 0) std::cout << std::to_string(*i) << std::endl;
    }
}
