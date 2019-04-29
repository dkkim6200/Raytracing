#include <iostream>
#include <math.h>

#include "vector3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "sphere.hpp"

Sphere::Sphere() {
    center = Vector3();
    radius = 0;
}

Sphere::Sphere(Vector3 center, float radius, Material *mat) {
    this->center = center;
    this->radius = radius;
    this->mat = mat;
}

bool Sphere::hit(Ray r, HitRecord &hitRec) {
    Vector3 oc = r.getOrigin() - center;
    
    float a = r.getDirection().dot(r.getDirection());
    float b = 2.0 * r.getDirection().dot(oc);
    float c = oc.dot(oc) - radius*radius;
    
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant >= 0) {
        float t = (-b - sqrt(discriminant)) / (2.0 * a);
        
        if (t > 0.001) {
            hitRec.pHit = r.pointAt(t);
            hitRec.normal = (hitRec.pHit - center).normalize();
            hitRec.mat = mat;
            return true;
        }
        
        t = (-b + sqrt(discriminant)) / (2.0 * a);
        
        if (t > 0.001) {
            hitRec.pHit = r.pointAt(t);
            hitRec.normal = (hitRec.pHit - center).normalize();
            hitRec.mat = mat;
            return true;
        }
    }
    
    return false;
}
