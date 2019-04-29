#ifndef METAL_H
#define METAL_H

class Vector3;
struct HitRecord;
class Ray;
class Material;

class Metal : public Material {
private:
    Vector3 albedo;
    float fuzziness;
    
public:
    Metal(Vector3 albedo, float fuzziness);
    
    virtual bool scatter(Ray r, HitRecord &hitRec, Vector3 &attenuation, Ray &scattered);
};

#endif
