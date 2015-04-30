#ifndef MYVEC
#define MYVEC
#include <memory>

struct my_vector {
        my_vector();
        my_vector(size_t size);
        my_vector(my_vector const &other);

        my_vector& operator =(my_vector const &other);

        size_t size() const;
        unsigned int& back();
        const unsigned int& back() const;


        inline unsigned int& operator[](size_t index){
            check_unique();
            return mode_pointer[index];
        }
        inline const unsigned int& operator[](size_t index) const{
            return mode_pointer[index];
        }

        void push_back(unsigned int val);
        void pop_back();

        void clear();
        void dump_modep();

    private:
        unsigned int small_object;
        std::shared_ptr<unsigned int> vec;
        unsigned int *mode_pointer;

        size_t current_size;
        size_t max_size;

        bool copy_flag;
        void ensure_capacity(size_t index);
        void check_unique();
};
#endif
