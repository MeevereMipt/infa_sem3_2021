//
// Created by EGor on 06.04.2021.
//

#ifndef MIPT2021_2SEM_MY_TREE_H
#define MIPT2021_2SEM_MY_TREE_H

namespace bin_tree {

    template <typename T>
    struct Node {
        Node* left;
        Node* right;
        T data;
        int height;

        explicit Node(T _data);
    };

    template <typename T>
    class BinTree {
        Node<T>* head;
        int height;

    public:
        BinTree();
        void insert(T data);
        bool search(T data);
    };

}

#endif //MIPT2021_2SEM_MY_TREE_H
