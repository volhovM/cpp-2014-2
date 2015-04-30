#include "set.h"
#include <iostream>


set::node::node(){
    value = 0;
    l = NULL;
    r = NULL;
    parent = NULL;
}

set::node::~node(){
    if (l != NULL) delete l;
    if (r != NULL) delete r;
}

set::node::node(int val){
    value = val;
    l = NULL;
    r = NULL;
    parent = NULL;
}

set::node::node(node *n){
    value = 0;
    l = NULL;
    r = NULL;
    parent = n;
}

set::node::node(node* par, int val){
    value = val;
    l = NULL;
    r = NULL;
    parent = par;
}

void set::node::dumpN(){
    std::cout << "{";
    if (l != NULL) l->dumpN(); else std::cout << " NIL ";
    std::cout << "|"  + std::to_string(value) + (parent == NULL ? " NOPARENT" : " P" + std::to_string(parent->value))+ " |";
    if (r != NULL) r->dumpN(); else std::cout << " NIL ";
    std::cout << "}";
}

void set::node::dumpNode(){
    std::cout << "value: " + std::to_string(value) + " parent: " /*+ (parent == NULL ? "X" : std::to_string(parent->value)) */<< std::endl;
}

size_t set::node::get_size(){
    size_t siz = 1;
    return siz + (l == NULL ? 0 : l->get_size()) + (r == NULL ? 0 : r->get_size());
}

bool operator==(set::node const& a, set::node const& b){
    if (a.value == b.value) {
        bool checkleft = true;
        bool checkright = true;
        if (a.l == NULL || b.l == NULL){
            if (a.l != b.l) return false;
            checkleft = false;
        }
        if (a.r == NULL || b.r == NULL){
            if (a.r != b.r) return false;
            checkright = false;
        }

        return ((!checkleft || *a.l == *b.l) && (!checkright || *a.r == *b.r));
    }
    return false;
}

////////////////////----------------------------------------------------------------------
set::~set(){
    delete root;
}

void set::dumpN(){ root->dumpN(); std::cout << std::endl; }

set::set(){
    root = new node(INT32_MAX);
    sz = 0;
}

set::set(set::node& a){
    root = new node(INT32_MAX);
    root->l = &a;
    a.parent = root;
    sz = a.get_size() + 1;
}

void set::copy_rec(node* cnode, node const* othernode){
    cnode->value = othernode->value;
    if (othernode->l != NULL) {
        if (cnode->l == NULL){
            cnode->l = new node(cnode);
        }
        copy_rec(cnode->l, othernode->l);
    }
    if (othernode->r != NULL) {
        if (cnode->r == NULL){
            cnode->r = new node(cnode);
        }
        copy_rec(cnode->r, othernode->r);
    }
}


set::set(set const& a){
    root = new node(INT32_MAX);
    sz = 0;
    try{
//        set b = a;
        copy_rec(root, a.root);
    } catch (...){
        delete root;
        throw;
    }
}

set& set::operator=(set const& a){
    set::node* temproot = new node(INT32_MAX);
    try{
        copy_rec(temproot, a.root);
    } catch (...){
        delete temproot;
        throw; //do i need this?
    }
    delete root;
    root = temproot;

    return *this;
}

size_t set::size() const{
    return sz;
}

bool set::empty() const{
    return sz == 0;
}

bool operator==(set const& a, set const& b){
//    std::cout << "== TREES";
    return *a.root == *b.root;
}

/////////////----------------------------------------------------------------------------------

bool operator==(set::iterator const& a, set::iterator const& b){
    return *a.it_node == *b.it_node;
}

set::iterator set::begin() const{
    node* curr = root;
    while (curr->l != NULL){
        curr = curr->l;
    }
    return iterator(curr);
}

set::iterator set::end() const{
    return set::iterator(root);
}
set::iterator set::find(int value) const{
    set::node* cur = root;
    while (true){
        if (value == cur->value){
            return iterator(cur);
        } else if (value < cur->value){
            if (cur->l == NULL) return end();
            cur = cur->l;
            continue;
        } else {
            if (cur->r == NULL) return end();
            cur = cur->r;
            continue;
        }
    }
}
set::iterator set::insert(int value){
    set::node* cur = root;
    while (true){
        if (value == cur->value){
            return iterator(cur);
        } else if (value < cur->value){
            if (cur->l == NULL) {
                cur->l = new set::node(cur, value);
                return iterator(cur->l);
            }
            cur = cur->l;
            continue;
        } else {
            if (cur->r == NULL) {
                cur->r = new set::node(cur, value);
                return iterator(cur->r);
            }
            cur = cur->r;
            continue;
        }
    }
}

set::iterator set::erase(iterator pos){
    if (pos == end()) return pos;
    set::node* cur = pos.getNode();
    iterator nxt = pos;
    nxt++;
    if (cur->l == NULL && cur->r == NULL){
        if (cur->parent->l == cur){
            cur->parent->l = NULL;
        } else {cur->parent->r = NULL;}
        delete cur;
        return nxt;
    } else if (cur->l == NULL || cur-> r == NULL){
        if (cur->l == NULL) {
            if (cur->parent->l == cur){
                cur->parent->l = cur->r;
            } else {
                cur->parent->r = cur->r;
            }
            cur->r->parent = cur->parent;
            cur->r = NULL;
            delete cur;
            return nxt;
        } else {
            if (cur->parent->l == cur){
                cur->parent->l = cur->l;
            } else {
                cur->parent->r = cur->l;
            }
            cur->l->parent = cur->parent;
            cur->l = NULL;
            delete cur;
            return nxt;
        }
    } else {
        cur->value = *nxt;
        erase(nxt);
        return cur;
    }
}


/////////////----------------------------------------------------------------------------------

set::iterator::iterator(node* nd){
    it_node = nd;
}

set::iterator& set::iterator::operator++(){
    node* curr = it_node;
    if (curr->r != NULL){
        curr = curr->r;
        while (curr->l != NULL){
            curr = curr->l;
        }
        it_node = curr;
    }
    else {
        while (curr->parent != NULL){
//            std::cout << "TESTTTT" << std::endl;
            if (curr->parent->l == curr) {
                it_node = curr->parent;
                break;
            }
            curr = curr->parent;
        }
    }
    return *this;
}

set::iterator set::iterator::operator++(int){
    iterator r = *this;
    ++*this;
    return r;
}

set::iterator& set::iterator::operator--(){
    node* curr = it_node;
    if (curr->l != NULL){
        curr = curr->l;
        while (curr->r != NULL){
            curr = curr->r;
        }
        it_node = curr;
    }
    else {
        while (curr->parent != NULL){
            if (curr->parent->r == curr) {
                it_node = curr->parent;
                break;
            }
            curr = curr->parent;
        }
    }
    return *this;
}
set::iterator set::iterator::operator--(int){
    iterator r = *this;
    --*this;
    return r;
}

int const& set::iterator::operator*() const{
    return it_node->value;
}

set::node* set::iterator::getNode(){
    return it_node;
}


bool operator!=(set const& a, set const& b){ return !(a == b); }
bool operator!=(set::node const& a, set::node const& b){ return !(a == b); }
bool operator!=(set::iterator const& a, set::iterator const& b){ return !(a == b); }
