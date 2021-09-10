//
// Created by Meevere on 4/14/2021.
//

#ifndef MIPT2021_2SEM_LIST_H
#define MIPT2021_2SEM_LIST_H

#include "deque.h"
#include <iterator>

using containers::deque::Deque;
using containers::deque::DequeNode;

using std::ostream;
using std::istream;

namespace containers::list {

    template <typename T>
    class List: public Deque<T>{
    public:
        List(): Deque<T>(){};

        List(std::initializer_list<T> list): Deque<T>(list){};

        List(const List& list): List(){
            for( auto iter = list.cbegin(); iter != list.cend(); ++iter ){
                (*this) << *iter;
            }
        }

        struct Iterator {
        private:
            DequeNode<T>* ptr;
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;

            explicit Iterator(DequeNode<T>* ptr) : ptr(ptr) {}

            reference operator*() const { return ptr->data; }
            pointer operator->() { return &(ptr->data); }

            // Prefix increment
            Iterator& operator++() { ptr = ptr->next; return *this; }

            // Postfix increment
            const Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }

            friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

        };

        List& operator= (const List& other){
            if( &other == this )
                return *this;
            while(this->length){
                this->pop_top();
            }
            for( auto iter = other.cbegin(); iter != other.cend(); ++iter){
                this->push_top(*iter);
            }
        }

        bool find( T data ){
            DequeNode<T>* cur_node = this->top;
            while(cur_node){
                if (cur_node->data == data)
                    return true;
                cur_node = cur_node->prev;
            }
            return false;
        }

        T operator[] (int index) const{
            if ( index < 0 or index >= this->length )
                throw std::out_of_range("bad index");
            int k = index;
            for(auto elem: *this){
                if( k == 0 )
                    return elem;
                k--;
            }
        }


        Iterator begin(){ return Iterator(this->bottom); }
        Iterator end(){ return Iterator(nullptr); }

        Iterator cbegin() const{ return Iterator(this->bottom); }
        Iterator cend() const{ return Iterator(nullptr); }
    };

    template<typename T>
    ostream & operator << (ostream &out, const List<T> &ls);
    template<typename T>
    istream & operator >> (istream &in, List<T> &ls);

    template <typename T>
    ostream & operator << (ostream &out, List<T> &ls) {
        out << "| ";
        for( auto elem : ls ){
            out << elem << ' ';
        }
        out << '|';
        return out;
    }

    template <typename T>
    istream & operator >> (istream &in, List<T> &ls) {
        T elem;
        in >> elem;
        elem >> ls;
        return in;
    }


}

#endif //MIPT2021_2SEM_LIST_H
