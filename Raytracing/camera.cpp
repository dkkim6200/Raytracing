#include <iostream>
#include <cmath>

#include "vector3.hpp"
#include "ray.hpp"
#include "camera.hpp"

Vector3 getRandomPointOnUnitDisk() {
    Vector3 p;
    
    do {
        p = 2.0 * Vector3(drand48(), drand48(), 0) - Vector3(1, 1, 0);
    } while (p.getSquaredMag() >= 1.0);
    
    return p;
}

Camera::Camera(Vector3 position, Vector3 lookAt, Vector3 up, float fov, float aspect, float aperture, float focusDistance) {
    lensRadius = aperture / 2;
    
    float theta = fov * M_PI / 180.0;
    float halfHeight = tan(theta / 2);
    float halfWidth = halfHeight * aspect;
    origin = position;
    
    w = (position - lookAt).normalize();
    u = up.cross(w).normalize(); // Camera right vector
    v = w.cross(u); // Camera up vector
    
    bottomLeft = origin - focusDistance * (halfWidth * u + halfHeight * v + w);
    horizontal = 2 * halfWidth * focusDistance * u;
    vertical = 2 * halfHeight * focusDistance * v;
}

Ray Camera::getRay(float s, float t) {
    Vector3 randomPointOnLens = lensRadius * getRandomPointOnUnitDisk();
    Vector3 offset = u * randomPointOnLens.x + v * randomPointOnLens.y;
    
    return Ray(origin + offset, bottomLeft + s * horizontal + t * vertical - origin - offset);
}

