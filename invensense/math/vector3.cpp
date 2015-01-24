#include "vector3.h"
#include <sstream>

template <class T>
Vector3<T>::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

template <class T>
Vector3<T>::Vector3(T x, T y, T z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
Vector3<T>::~Vector3()
{

}

template <class T>
string Vector3<T>::toString()
{
    stringstream sstr;
    sstr << "Vector3 (";
    sstr << dec << (double) x << ", ";
    sstr << dec << (double) y << ", ";
    sstr << dec << (double) z;
    sstr << ")";
    return sstr.str();
}

template class Vector3<short>;
template class Vector3<int>;
template class Vector3<long>;
template class Vector3<long long>;
template class Vector3<float>;
template class Vector3<double>;
template class Vector3<unsigned char>;
