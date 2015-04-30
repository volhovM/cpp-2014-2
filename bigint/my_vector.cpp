#include <memory>
#include <cstring>
#include <iostream>
#include "my_vector.h"

using namespace std;

static void delete_array(unsigned int* z)
{
    delete[] z;
}

my_vector::my_vector() : vec(NULL, delete_array){
    mode_pointer = &small_object;
    current_size = 0;
    max_size = 1;
}

my_vector::my_vector(size_t size) : vec(NULL, delete_array){
    if (size <= 1) {
        mode_pointer = &small_object;
        current_size = 0;
        max_size = 1;
    } else {
        unsigned int* a = new unsigned int[size];
        for (size_t i = 0; i < size; i++) a[i] = 0;
        vec.reset(a, delete_array);
        max_size = size;
        current_size = size;
        mode_pointer = vec.get();
    }
    copy_flag = false;
}

my_vector::my_vector(my_vector const &other) : vec(NULL, delete_array){
    small_object = other.small_object;
    current_size = other.current_size;
    max_size = other.max_size;

    if (other.mode_pointer == &other.small_object){
        small_object = other.small_object;
        mode_pointer = &small_object;
    } else {
        vec = other.vec;
        mode_pointer = vec.get();
    }
    copy_flag = true;
}


my_vector& my_vector::operator=(my_vector const &other){
    small_object = other.small_object;
    current_size = other.current_size;
    max_size = other.max_size;
    if (other.mode_pointer == &other.small_object){
        small_object = other.small_object;
        mode_pointer = &small_object;
    } else {
        vec = other.vec;
        mode_pointer = vec.get();
    }
    copy_flag = true;
    return *this;
}

size_t my_vector::size() const{
    return current_size;
}

unsigned int& my_vector::back(){
    check_unique();
    return mode_pointer[current_size - 1];
}
const unsigned int& my_vector::back() const{
    return mode_pointer[current_size - 1];
}


void my_vector::push_back(unsigned int val){
    ensure_capacity(current_size + 1);
    mode_pointer[current_size - 1] = val;
}

void my_vector::pop_back(){
    ensure_capacity(current_size - 1);
}

void my_vector::clear(){
    check_unique();
    mode_pointer = &small_object;
    current_size = 0;
    max_size = 1;
    vec.reset();
}

void my_vector::ensure_capacity(size_t index){
    check_unique();
    if (mode_pointer == vec.get() && index > max_size) { //expanding vector
        max_size = index * 2;
        unsigned int* maxs = new unsigned int[max_size];
        memcpy(maxs, vec.get(), sizeof(unsigned int) * current_size);
        vec.reset(maxs, delete_array);
        mode_pointer = vec.get();
    } else if (mode_pointer == &small_object && index > 1) { //expanding small object to vector
        max_size = max_size * 2;
        vec.reset(new unsigned int[max_size], delete_array);
        mode_pointer = vec.get();
        memcpy(mode_pointer, &small_object, sizeof(unsigned int) * current_size);
    }
    current_size = index;
    copy_flag = false;
}

void my_vector::check_unique(){
    if (!vec.unique() && mode_pointer == vec.get()) {
//        cout << "UNIQUE" << endl;
        unsigned int* maxs = new unsigned int[max_size];
        memcpy(maxs, vec.get(), current_size * sizeof(unsigned int)); //int??
        vec.reset(maxs, delete_array);
        mode_pointer = vec.get();
        copy_flag = false;
    }
}

void my_vector::dump_modep(){
    if (mode_pointer == vec.get()) cout << "Vs";
    else cout << "SOs";
    cout << "(" + to_string(current_size) + " : " + to_string(max_size) + ") ";
    for (size_t i = 0; i < current_size; i++){
        cout << "[" + to_string(mode_pointer[i]) + "] ";
    }
    for (size_t i = current_size; i < max_size; i++){
        cout << "[X] ";
    }
    cout << endl;
}
