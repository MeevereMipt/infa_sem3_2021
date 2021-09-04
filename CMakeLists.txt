cmake_minimum_required(VERSION 3.20)
project(infa_sem3_2021)

set(CMAKE_CXX_STANDARD 20)

set(USABLES_FILES
        usables/containers/stack.h
        usables/containers/deque.h
        usables/my_tree.cpp
        usables/my_tree.h
        usables/containers/array.h
        usables/graph.h
        usables/graph.cpp
        usables/containers/cyclic_array.h
        usables/containers/list.h)

add_executable(infa_sem3_2021

        ${USABLES_FILES}

        main.cpp)