//
// Created by EGor on 06.04.2021.
//

#include "my_tree.h"

using namespace bin_tree;

template<typename T>
Node<T>::Node(T _data) {
    height = 0;
    data = _data;
    left = nullptr;
    right = nullptr;
}

template<typename T>
BinTree<T>::BinTree() {
    head = nullptr;
    height = 0;
}

template<typename T>
bool BinTree<T>::search(T data) {
    Node<T> *cur_node = head;
    Node<T> *prev_node = nullptr;
    while (cur_node != nullptr) {
        prev_node = cur_node;
        if (data < cur_node->data)
            cur_node = cur_node->left;
        else
            cur_node = cur_node->right;
    }
    return prev_node->data == data;
}

template<typename T>
void BinTree<T>::insert(T data) {
    Node<T>* cur_node = head; Node<T>* prev_node = nullptr;
    while( cur_node != nullptr ){
        prev_node = cur_node;
        if (data < cur_node->data)
            cur_node = cur_node->left;
        else
            cur_node = cur_node->right;
    }
    cur_node = new Node(data);
    data < cur_node->data ? prev_node->left = cur_node : prev_node->right = cur_node;
}
