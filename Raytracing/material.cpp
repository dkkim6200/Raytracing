#include <iostream>
#include <cmath>

#include "vector3.hpp"
#include "hitable.hpp"
#include "material.hpp"

Vector3 Material::getRandomPointInUnitSphere() {
    Vector3 p;
    
    do {
        p = 2.0 * Vector3(drand48(), drand48(), drand48()) - Vector3(1, 1, 1);
    } while (p.getSquaredMag() >= 1.0);
    
    return p;
}

Vector3 Material::reflect(Vector3 incident, Vector3 normal) {
    return incident - 2 * (incident.dot(normal)) * normal;
}

bool Material::refract(Vector3 incident, Vector3 normal, float n1_over_n2, Vector3 &refracted) {
    Vector3 v = incident.normalize();
    float v_dot_n = v.dot(normal);
    float discriminant = 1.0 - n1_over_n2 * n1_over_n2 * (1 - v_dot_n * v_dot_n);
    
    if (discriminant > 0) {
        refracted = n1_over_n2 * (v - v_dot_n * normal) - normal * sqrt(discriminant);
        return true;
    }
    else {
        return false;
    }
}

float Material::schlick(float cosineIncident, float refractiveIndex) {
    float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
    r0 = r0 * r0;
    
    return r0 + (1 - r0) * pow((1 - cosineIncident), 5);
}
