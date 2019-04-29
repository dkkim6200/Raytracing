#include <iostream>
#include <math.h>

#include "vector3.hpp"

using namespace std;

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::~Vector3() {
}

void Vector3::operator=(const Vector3 &vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

Vector3 Vector3::operator+(const Vector3 &vec) {
    Vector3 result = Vector3(x + vec.x, y + vec.y, z + vec.z);
    return result;
}

Vector3 Vector3::operator+=(const Vector3 &vec) {
    (*this) = (*this) + vec;
    return (*this);
}

Vector3 Vector3::operator-(const Vector3 &vec) {
    Vector3 result = Vector3(x - vec.x, y - vec.y, z - vec.z);
    return result;
}

Vector3 Vector3::operator-=(const Vector3 &vec) {
    (*this) = (*this) - vec;
    return (*this);
}

Vector3 Vector3::operator*(const float scalar) {
    Vector3 result = Vector3(x * scalar, y * scalar, z * scalar);
    return result;
}

Vector3 operator*(const float scalar, Vector3 v) {
    return v * scalar;
}

Vector3 Vector3::operator*(const Vector3 &vec) {
    return Vector3(x * vec.x, y * vec.y, z * vec.z);
}

Vector3 Vector3::operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    
    return (*this);
}

Vector3 Vector3::operator/(const float scalar) {
    Vector3 result = Vector3(x / scalar, y / scalar, z / scalar);
    return result;
}

ostream& operator<<(ostream& os, const Vector3 &vec) {
    os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
    
    return os;
}

float Vector3::getMagnitude() {
    return sqrt(x*x + y*y + z*z);
}

float Vector3::getSquaredMag() {
    return x*x + y*y + z*z;
}

Vector3 Vector3::normalize() {
    return (*this) / getMagnitude();
}

float Vector3::dot(Vector3 vec) {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::cross(Vector3 vec) {
    Vector3 result = Vector3(y * vec.z - z * vec.y,
                             z * vec.x - x * vec.z,
                             x * vec.y - y * vec.x);
    return result;
}

float Vector3::projectScalar(Vector3 vec) {
    return dot(vec) / vec.getMagnitude(); // <a> * <b> / |b|
}

Vector3 Vector3::projectVector(Vector3 vec) {
    return vec * (dot(vec) / vec.dot(vec));
}
