#ifndef MATERIAL_H
#define MATERIAL_H

class Ray;
struct HitRecord;
class Vector3;

class Material {
protected:
    Vector3 getRandomPointInUnitSphere();
    Vector3 reflect(Vector3 incident, Vector3 normal);
    bool refract(Vector3 incident, Vector3 normal, float n1_over_n2, Vector3 &refracted);
    float schlick(float cosineIncident, float refractiveIndex);
    
public:
    virtual bool scatter(Ray r, HitRecord &hitRec, Vector3 &attenuation, Ray &scattered) = 0;
};

#endif
