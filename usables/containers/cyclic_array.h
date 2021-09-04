//
// Created by Meevere on 4/14/2021.
//

#ifndef MIPT2021_2SEM_CYCLIC_ARRAY_H
#define MIPT2021_2SEM_CYCLIC_ARRAY_H

#include "containers/array.h"

namespace containers::array {

    template <typename T>
    class CyclicArray: public Array<T>{
        T* _arr;
        int _size;
    public:
        using Array<T>::Array;

        T& operator [] (int i){
            if( i < 0 ){
                i = _size-(-i)%_size;
            }
            return _arr[i % _size];
        }

        T operator [] (int i) const{
            if( i < 0 ){
                i = _size-(-i)%_size;
            }
            return _arr[i % _size];
        }
    };

}

#endif //MIPT2021_2SEM_CYCLIC_ARRAY_H
