#include <iostream>
#include "vector3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "material.hpp"
#include "lambertian.hpp"

Lambertian::Lambertian(Vector3 albedo) {
    this->albedo = albedo;
}

bool Lambertian::scatter(Ray r, HitRecord &hitRec, Vector3 &attenuation, Ray &scattered) {
    Vector3 target = hitRec.pHit + hitRec.normal + getRandomPointInUnitSphere();
    scattered = Ray(hitRec.pHit, target - hitRec.pHit);
    attenuation = albedo;
    
    return true;
}
