#ifndef HITABLE_H
#define HITABLE_H

class Ray;
class Vector3;
class Material;

struct HitRecord {
    Vector3 pHit;
    Vector3 normal;
    Material *mat;
};

class Hitable {
public:
    virtual bool hit(Ray r, HitRecord &hitRec) = 0;
};

#endif
