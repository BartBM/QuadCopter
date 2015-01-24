#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>

using namespace std;

template <class T>
class Vector3
{
public:
    Vector3();
    Vector3(T x, T y, T z);
    ~Vector3();

    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }
    void setZ(T z) { this->z = z; }

    T getX() const { return x; }
    T getY() const { return y; }
    T getZ() const { return z; }

    //casting

    template<typename C>
    Vector3<T> (const Vector3<C> &rhs)
    {
        x = (T) rhs.getX();
        y = (T) rhs.getY();
        z = (T) rhs.getZ();
    }

    template <typename C>
    operator Vector3<C>()
    {
        Vector3<C> result;
        result.setX((C) getX());
        result.setY((C) getY());
        result.setZ((C) getZ());
        return result;
    }

    template<typename C>
    Vector3  operator=( const Vector3< C > &rhs )
    {
        setX((C) rhs.getX());
        setY((C) rhs.getY());
        setZ((C) rhs.getZ());
        return *this;
    }

    // addition

    Vector3<T>& operator+= (T value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }

    Vector3<T>& operator+= (Vector3<short> value)
    {
        x += value.getX();
        y += value.getY();
        z += value.getZ();
        return *this;
    }

    friend Vector3<T> operator+ (Vector3<T> vector3, T value)
    {
        Vector3<T> temp;
        temp.setX(vector3.getX() + value);
        temp.setY(vector3.getY() + value);
        temp.setZ(vector3.getZ() + value);
        return temp;
    }

    // subtraction

    Vector3<T>& operator-= (Vector3<T> value)
    {
        x -= value.getX();
        y -= value.getY();
        z -= value.getZ();
        return *this;
    }

    friend Vector3<T> operator- (Vector3<T> left, Vector3<T> right)
    {
        Vector3<T> temp;
        temp.setX(left.getX() - right.getX());
        temp.setY(left.getY() - right.getY());
        temp.setZ(left.getZ() - right.getZ());
        return temp;
    }

    friend Vector3<T> operator- (Vector3<T> vector3, T value)
    {
        Vector3<T> temp;
        temp.setX(vector3.getX() - value);
        temp.setY(vector3.getY() - value);
        temp.setZ(vector3.getZ() - value);
        return temp;
    }

    // bitwise operators

    friend Vector3<T> operator& (Vector3<T> vector3, T value)
    {
        Vector3<T> temp;
        temp.setX(vector3.getX() & value);
        temp.setY(vector3.getY() & value);
        temp.setZ(vector3.getZ() & value);
        return temp;
    }

    // division

    Vector3<T>& operator/= (T value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    friend Vector3<T> operator/ (Vector3<T> vector3, T value)
    {
        Vector3<T> temp;
        temp.setX(vector3.getX() / value);
        temp.setY(vector3.getY() / value);
        temp.setZ(vector3.getZ() / value);
        return temp;
    }

    // multiplication

    Vector3<T>& operator*= (T value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    friend Vector3<T> operator* (T value, Vector3<T> vector3)
    {
        Vector3<T> temp;
        temp.setX(vector3.getX() * value);
        temp.setY(vector3.getY() * value);
        temp.setZ(vector3.getZ() * value);
        return temp;
    }

    friend Vector3<T> operator* (Vector3<T> vector3, T value)
    {
        Vector3<T> temp;
        temp.setX(vector3.getX() * value);
        temp.setY(vector3.getY() * value);
        temp.setZ(vector3.getZ() * value);
        return temp;
    }

    template<typename C>
    friend Vector3<T> operator* (Vector3<T> left, Vector3<C> right)
    {
        Vector3<T> temp;
        temp.setX(left.getX() * right.getX());
        temp.setY(left.getY() * right.getY());
        temp.setZ(left.getZ() * right.getZ());
        return temp;
    }

    string toString();

private:
    T x, y, z;
};

#endif // VECTOR3_H
