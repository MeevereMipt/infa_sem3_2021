//
// Created by meeve on 04.09.2021.
//

#ifndef INFA_SEM3_2021_SET_H
#define INFA_SEM3_2021_SET_H

#include "containers/list.h"
#include "containers/stack.h"

namespace containers::set {
    using std::ostream;
    using std::istream;

    using containers::list::List;
    using containers::stack::Stack;

    template <typename T>
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node() {left = right = nullptr;}
        explicit Node(const T& data) : Node(), data(data) {}

        ~Node() {
            delete left; delete right;
            delete data;
        }

        bool connect(const Node& node) {
            if( node.data == data) return false;
            if( node.data < data ){
                if(left != nullptr)
                    return left->connect(node);
                left = &node;
            } else {
                if(right != nullptr)
                    return right->connect(node);
                right = &node;
            }
            return true;
        }



        ostream& operator<<(ostream& out, Node<T> node){
            return out << node;
        }
    };

    template <typename T>
    class Set {
    protected:
        Node<T>* head = nullptr;
        int size = 0;

        Node<T>* _find(const T& data){
            auto cur_node = head;
            while(cur_node->data != data){
                if( data < cur_node->data )
                    cur_node = cur_node->left;
                else
                    cur_node = cur_node->right;
                if(!cur_node) return nullptr;
            }
            return cur_node;
        }

    public:
        Set() = default;
        explicit Set(const T& data) : Set(), size(1) {
            head = new Node<T>(data);
        }

        bool insert(const T& data) {
            auto node = new Node<T>(data);
            return head->connect(node);
        };

        bool find(const T& data) {
            return _find(data) != nullptr;
        }

        List<T> to_list(){
            Stack<Node<T>*> stack;
            stack.push(head);


        }




        bool remove(const T& data) {
            auto cur_node = head; Node<T>* prev_node = nullptr;

            while(cur_node->data != data){
                prev_node = cur_node;
                if( data < cur_node->data )
                    cur_node = cur_node->left;
                else
                    cur_node = cur_node->right;
                if(!cur_node) return false; //node was not found
            }

            // since we lost information of in which direction is
            // current node we need to check it again
            if( cur_node->data < prev_node->data ){
                prev_node->left = cur_node->right;
            } else
                prev_node->right = cur_node->right;

            // TODO: to make remove method properly merge must be implemented beforehand
            return true;
        }

    };


}

#endif //INFA_SEM3_2021_SET_H
