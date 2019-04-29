#include <iostream>

#include "vector3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "material.hpp"
#include "metal.hpp"

Metal::Metal(Vector3 albedo, float fuzziness) {
    this->albedo = albedo;
    this->fuzziness = fuzziness;
}

bool Metal::scatter(Ray r, HitRecord &hitRec, Vector3 &attenuation, Ray &scattered) {
    Vector3 reflected = reflect(r.getDirection().normalize(), hitRec.normal);
    
    scattered = Ray(hitRec.pHit, reflected + fuzziness * getRandomPointInUnitSphere());
    attenuation = albedo;
    return (reflected.dot(hitRec.normal) > 0);
}
