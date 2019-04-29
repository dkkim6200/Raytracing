#ifndef SPHERE_H
#define SPHERE_H

class Hitable;
class Vector3;
class Ray;
class Material;

class Sphere : public Hitable {
private:
    Vector3 center;
    float radius;
    Material *mat;
    
public:
    Sphere();
    Sphere(Vector3 center, float radius, Material *mat);
    virtual bool hit(Ray r, HitRecord &hitRec);
};

#endif
