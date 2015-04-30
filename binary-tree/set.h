#include <memory>
#include <iostream>

struct set {
    ~set();
    set();
    set(set const&);
    set& operator=(set const&);

    size_t size() const;
    bool empty() const;

    struct iterator;
    struct node;
    set(node& a);
    iterator begin() const;
    iterator end() const;
    iterator find(int value) const;
    iterator insert(int value);
    iterator erase(iterator pos);

    friend bool operator==(set const& a, set const& b);
    friend bool operator!=(set const& a, set const& b);
    void dumpN();

private:
    void copy_rec(node* cnode, node const* othernode);
    node* root;
    size_t sz;
};

bool operator==(set const& a, set const& b);
bool operator==(set::node const& a, set::node const& b);
bool operator==(set::iterator const& a, set::iterator const& b);
bool operator!=(set const& a, set const& b);
bool operator!=(set::node const& a, set::node const& b);
bool operator!=(set::iterator const& a, set::iterator const& b);

struct set::iterator {
    iterator(node* nd);

    set::node* getNode();

    friend bool operator==(set::iterator const& a, set::iterator const& b);
    friend bool operator!=(set::iterator const& a, set::iterator const& b);

    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    int const& operator*() const;

private:
    set::node* it_node;
};

struct set::node {
    node();
    ~node();
    node(int value);
    //parent n
    node(node* par);
    node(node* par, int value);

    friend bool operator==(node const& a, node const& b);
    friend bool operator!=(node const& a, node const& b);

    void dumpN();
    void dumpNode();
    size_t get_size();

    int value;
    set::node* l;
    set::node* r;
    set::node* parent;
};
