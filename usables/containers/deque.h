//
// Created by Meevere on 3/8/2021.
//

#ifndef MIPT2021_2SEM_MY_Deque_H
#define MIPT2021_2SEM_MY_Deque_H

#include <iostream>

namespace containers::deque {

    template<typename T>
    struct DequeNode {
        T data;
        DequeNode *next;
        DequeNode *prev;

        explicit DequeNode(T x) {
            prev = nullptr;
            next = nullptr;
            data = x;
        }

        void connect_next(DequeNode *node);
        void connect_prev(DequeNode *node);
    };

    template<typename T>
    class Deque {
    protected:
        DequeNode<T> *top;
        DequeNode<T> *bottom;
    public:
        int length = 0;

        Deque() {
            this->top = this->bottom = nullptr;
            length = 0;
        }

        Deque(std::initializer_list<T> list): Deque(){
            for( auto elem : list ){
                *this << elem;
            }
        }

        ~Deque(){
            while(length != 0){
                pop_bottom();
            }
        }

        void push_top(T data);
        void push_bottom(T data);

        T pop_top();
        T pop_bottom();

    };

    template<typename Y>
    Deque<Y> &operator<<(Deque<Y> &q, Y data);
    template<typename Y>
    Deque<Y> &operator>>(Deque<Y> &q, Y &data);
    template<typename Y>
    Deque<Y> &operator<<(Y &data, Deque<Y> &q);
    template<typename Y>
    Deque<Y> &operator>>(Y data, Deque<Y> &q);

    ////////////////////////////////////////
    //C++ why you do this to me

    template <typename T>
    void DequeNode<T>::connect_next(DequeNode *node) {
        this->next = node;
        if (node != nullptr)
            node->prev = this;
    }

    template <typename T>
    void DequeNode<T>::connect_prev(DequeNode<T> *node) {
        this->prev = node;
        if (node != nullptr)
            node->next = this;
    }

    template <typename T>
    void Deque<T>::push_top(T const data) {
        auto elem = new DequeNode(data);
        elem->connect_prev(this->top);

        if (length == 0) {
            bottom = elem;
        }

        top = elem;
        length++;
    }

    template <typename T>
    void Deque<T>::push_bottom(T const data) {
        auto elem = new DequeNode(data);
        elem->connect_next(bottom);

        if (length == 0) {
            top = elem;
        }

        bottom = elem;
        length++;
    }

    template <typename T>
    T Deque<T>::pop_top() {
        auto prev_top = this->top;
        if (prev_top == nullptr)
            throw std::underflow_error("pop with empty Deque");

        T data = prev_top->data;
        this->top = prev_top->prev;
        if(this->top)
            this->top->next = nullptr;

        delete prev_top;
        length--;
        return data;
    }

    template <typename T>
    T Deque<T>::pop_bottom() {
        auto prev_bottom = this->bottom;
        if (prev_bottom == nullptr)
            throw std::underflow_error("pop with empty Deque");

        T data = prev_bottom->data;
        this->bottom = prev_bottom->next;
        if(this->bottom)
            this->bottom->prev = nullptr;

        delete prev_bottom;
        length--;
        return data;
    }

    template <typename T>
    Deque<T>& operator<<(Deque<T> &q, const T data) {
        q.push_top(data);
        return q;
    }

    template <typename T>
    Deque<T>& operator>>(Deque<T> &q, T &data) {
        data = q.pop_top();
        return q;
    }

    template <typename T>
    Deque<T>& operator<<(T &data, Deque<T> &q) {
        data = q.pop_bottom();
        return q;
    }

    template <typename T>
    Deque<T>& operator>>(const T data, Deque<T> &q) {
        q.push_bottom(data);
        return q;
    }

}
#endif //MIPT2021_2SEM_MY_Deque_H
