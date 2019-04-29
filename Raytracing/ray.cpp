#include <iostream>
#include "vector3.hpp"
#include "ray.hpp"

Ray::Ray() {
    origin = Vector3();
    direction = Vector3();
}

Ray::Ray(Vector3 origin, Vector3 direction) {
    this->origin = origin;
    this->direction = direction;
}

Vector3 Ray::getOrigin() {
    return origin;
}

Vector3 Ray::getDirection() {
    return direction;
}

Vector3 Ray::pointAt(float t) {
    return origin + t * direction;
}
