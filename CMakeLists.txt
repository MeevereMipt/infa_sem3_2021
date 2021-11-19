cmake_minimum_required(VERSION 3.17)
project(infa_sem3_2021)

set(CMAKE_CXX_STANDARD 20)

set(APP_USABLES usables/)

include_directories(${APP_USABLES})

set(USABLES_FILES
        usables/containers/stack.h
        usables/containers/deque.h
        usables/my_tree.cpp
        usables/my_tree.h
        usables/containers/array.h
        usables/graph.h
        usables/graph.cpp
        usables/containers/cyclic_array.h
        usables/containers/list.h usables/containers/set.h control/taskD.cpp control/taskD.h control/taskC.cpp control/taskC.h control/taskB.cpp control/taskB.h)

add_executable(infa_sem3_2021

        ${USABLES_FILES}

        main.cpp control/taskE.cpp control/taskE.h control/taskA.cpp control/taskA.h)