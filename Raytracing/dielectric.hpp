#ifndef DIELECTRIC_H
#define DIELECTRIC_H

class Vector3;
class Ray;
class Material;

class Dielectric : public Material {
private:
    Vector3 albedo;
    float refractiveIndex;
    
public:
    Dielectric(Vector3 albedo, float refractiveIndex);
    
    virtual bool scatter(Ray r, HitRecord &hitRec, Vector3 &attenuation, Ray &scattered);
};

#endif

