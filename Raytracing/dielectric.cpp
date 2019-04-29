#include <iostream>
#include <cmath>

#include "vector3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "material.hpp"
#include "dielectric.hpp"

Dielectric::Dielectric(Vector3 albedo, float refractiveIndex) {
    this->albedo = albedo;
    this->refractiveIndex = refractiveIndex;
}

bool Dielectric::scatter(Ray r, HitRecord &hitRec, Vector3 &attenuation, Ray &scattered) {
    attenuation = albedo;
    
    Vector3 normal;
    Vector3 reflected = reflect(r.getDirection(), hitRec.normal);
    Vector3 refracted;
    
    float n1_over_n2 = 0;
    float reflectionCoefficient = 0; // Probability of an incident photon being reflected.
    float cosineIncident = 0;
    
    // Dealing with Ray Enter/Exit Object
    
    // If the incident ray is in the same direction as the normal, the ray is being shoot outside to the vacuum.
    // n1_over_n2 = refractiveIndex
    // Surface normal must be inverted, as was the assumption of the calculation
    if (r.getDirection().dot(hitRec.normal) > 0) {
        normal = hitRec.normal * -1;
        n1_over_n2 = refractiveIndex;
        cosineIncident = r.getDirection().normalize().dot(hitRec.normal);
    }
    // If the incident ray is the opposite direction as the normal, the ray is entering the object.
    // n1_over_n2 = 1 / refractiveIndex
    else {
        normal = hitRec.normal;
        n1_over_n2 = 1.0 / refractiveIndex;
        cosineIncident = -r.getDirection().normalize().dot(hitRec.normal);
    }
    
    // Dealing with Ray Reflection/Refraction (Fresnel)
    
    // If refracted ray exists
    if (refract(r.getDirection(), normal.normalize(), n1_over_n2, refracted)) {
        // Then only refract some of the rays according to Schlick's approximation
        reflectionCoefficient = schlick(cosineIncident, refractiveIndex);
    }
    // If there is no refracted ray
    else {
        // Then all incident rays get reflected. Total reflection
        reflectionCoefficient = 1.0;
    }
    
    // If a random number between 0.0 and 1.0 is smaller than the reflection coefficient R(theta),
    if (drand48() < reflectionCoefficient) {
        // Then this ray of photon gets reflected
        scattered = Ray(hitRec.pHit, reflected);
    }
    // If the random number is greater than ~...
    else {
        // Then this ray of photon gets refracted into the object
        scattered = Ray(hitRec.pHit, refracted);
    }
    
    return true;
}

