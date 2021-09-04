//
// Created by Meevere on 3/6/2021.
//

#ifndef MIPT2021_2SEM_STACK_H
#define MIPT2021_2SEM_STACK_H

namespace containers::stack {

    template<typename T>
    struct StackNode {
        explicit StackNode(T x) {
            data = x;
            next = nullptr;
        }
        T data;
        StackNode *next;
    };

    template<typename T>
    class Stack {
    protected:
        StackNode<T> *top;
    public:
        // for decorative purposes
        int length;

        Stack() {
            top = nullptr;
            length = 0;
        }
        ~Stack() {
            while (!is_empty()) {
                pop();
            }
        }

        void push(T n);
        T pop();

        bool is_empty() {
            return top == nullptr;
        }
    };

    //////////////////////////////////////////////////////
    ///////Implementation/////////////////////////////////
    ////////////////////////////////whyc++issofknghorrible

    template <typename T>
    T Stack<T>::pop() {
        if (top == nullptr)
            throw std::underflow_error("pop with nullptr");

        int out;
        StackNode<T>* prev_top = top;

        out = top->data;
        top = top->next;

        length--;
        delete prev_top;
        return out;
    }

    template <typename T>
    void Stack<T>::push(T n) {
        auto *elem = new StackNode<T>(n);
        elem->next = top;
        top = elem;
        length++;
    }

}

#endif //MIPT2021_2SEM_STACK_H
