#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

class Material;
class Vector3;
struct HitRecord;

class Lambertian : public Material {
private:
    Vector3 albedo;
    
public:
    Lambertian(Vector3 albedo);
    
    virtual bool scatter(Ray r, HitRecord &hitRec, Vector3 &attenuation, Ray &scattered);
};

#endif
