//
// Created by zui on 2/2/23.
//

#ifndef OGLGE_TIME_H
#define OGLGE_TIME_H

namespace GECore {

    template<typename T>
    struct BasicTime {
        template<class U>
        BasicTime(U t_) : t{t_} {}

        T getSeconds() { return t; }
        T getMilliseconds() { return t * 1000; }

        T operator*(BasicTime<T> b);

        static T Neg(T t) {
            return -t;
        }

        typedef T type;
        T t;
    };

    template<typename T>
    T BasicTime<T>::operator*(BasicTime<T> b) {
        return t * b.t;
    }

    using Time = BasicTime<double>;

}

#endif //OGLGE_TIME_H
