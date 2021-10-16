//
// Created by wlxklyh on 2021/10/16.
//

#include "Vec3.h"

namespace RMath {
    template<class T>
    inline std::istream &operator>>(std::istream &is, Vec3<T> &v) {
        is >> v.e[0] >> v.e[1] >> v.e[2];
        return is;
    }

    template<class T>
    inline std::ostream &operator<<(std::ostream &os, Vec3<T> &v) {
        os << v.e[0] << v.e[1] << v.e[2];
        return os;
    }

    template<class T>
    inline void Vec3<T>::make_unit_vector() {
        float k = 1.0 / length();
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
    }

    template<class T>
    inline Vec3<T> &Vec3<T>::operator+=(const Vec3<T> &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    template<class T>
    inline Vec3<T> &Vec3<T>::operator-=(const Vec3<T> &v) {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }

    template<class T>
    inline Vec3<T> &Vec3<T>::operator*=(const Vec3<T> &v) {
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }

    template<class T>
    inline Vec3<T> &Vec3<T>::operator/=(const Vec3<T> &v) {
        e[0] /= v.e[0];
        e[1] /= v.e[1];
        e[2] /= v.e[2];
        return *this;
    }

    template<class T>
    inline Vec3<T> &Vec3<T>::operator/=(const T v) {
        e[0] /= v;
        e[1] /= v;
        e[2] /= v;
        return *this;
    }

    template<class T>
    inline Vec3<T> &Vec3<T>::operator*=(const T v) {
        e[0] *= v;
        e[1] *= v;
        e[2] *= v;
        return *this;
    }
}

