#ifndef RAY_H
#define RAY_H

class Vector3;

class Ray {
private:
    Vector3 origin;
    Vector3 direction;
    
public:
    Ray();
    Ray(Vector3 origin, Vector3 direction);
    
    Vector3 getOrigin();
    Vector3 getDirection();
    Vector3 pointAt(float t);
};

#endif
