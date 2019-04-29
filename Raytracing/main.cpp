#include <iostream>
#include <fstream>
#include <math.h>

#include "vector3.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "hitable.hpp"
#include "hitable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"

using namespace std;

//        return 0.5 * (normal + Vector3(1.0, 1.0, 1.0));

#define MAX_REFLECTION_DEPTH 50

Vector3 getSky(Ray r) {
    Vector3 unitDirection = r.getDirection().normalize();
    float t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
}

Vector3 getColor(Ray r, Hitable *world, int depth) {
    HitRecord hitRec;
    
    if (world->hit(r, hitRec)) {
        Ray scattered;
        Vector3 attenuation;
        
        if (depth < MAX_REFLECTION_DEPTH && hitRec.mat->scatter(r, hitRec, attenuation, scattered)) {
            return attenuation * getColor(scattered, world, depth + 1);
        }
        else {
            return Vector3(0, 0, 0);
        }
        
//        Vector3 target = hitRec.pHit + hitRec.normal + getRandomPoint();
//        return 0.9 * getColor(Ray(hitRec.pHit, target - hitRec.pHit), world, depth+1);
    }
    else {
        return getSky(r);
    }
}

Hitable *getRandomScene() {
    int numSpheres = 500;
    Hitable **list = new Hitable*[numSpheres + 1];
    
    list[0] = new Sphere(Vector3(0, -1000, 0), 1000, new Lambertian(Vector3(0.5, 0.5, 0.5)));
    
    int i = 1;
    
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            Vector3 center = Vector3(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            
            if ((center - Vector3(4, 0.2, 0)).getMagnitude() > 0.9) {
                float chooseMat = drand48();
                
                if(chooseMat < 0.8) {
                    list[i++] = new Sphere(center, 0.2, new Lambertian(Vector3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
                }
                else if (chooseMat < 0.95) {
                    list[i++] = new Sphere(center, 0.2, new Metal(Vector3(0.5 * (1.0 + drand48()), 0.5 * (1.0 + drand48()), 0.5 * (1.0 + drand48())), 0.5 * drand48()));
                }
                else {
                    list[i++] = new Sphere(center, 0.2, new Dielectric(Vector3(1, 1, 1), 1.5));
                }
            }
        }
    }
    
    list[i++] = new Sphere(Vector3(0, 1, 0), 1.0, new Dielectric(Vector3(1, 1, 1), 1.5));
    list[i++] = new Sphere(Vector3(-4, 1, 0), 1.0, new Lambertian(Vector3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vector3(4, 1, 0), 1.0, new Metal(Vector3(0.7, 0.6, 0.6), 0.0));
    
    return new HitableList(list, i);
}

int main(int argc, const char * argv[]) {
    ofstream file;
    file.open("/Users/DaekunKim/Documents/Programming/Raytracing/output.ppm");
    
    int width = 800;
    int height = 400;
    int numAliasingSamples = 100;
    
    file << "P3" << endl;
    file << width << " " << height << endl;
    file << "255" << endl;
    
//    Hitable **list = new Hitable*[4];
//    list[0] = new Sphere(Vector3(0, -(5000+0.5), -1.0), 5000, new Lambertian(Vector3(1, 1, 1)));
//    list[1] = new Sphere(Vector3(0, 0, -1.0), 0.5, new Dielectric(Vector3(1, 1, 1), 1.5));
//    list[2] = new Sphere(Vector3(-.8, 0, -1.0 - 0.5), 0.5, new Lambertian(Vector3(0.1, 0.2, 0.5)));
//    list[3] = new Sphere(Vector3(.8, 0, -1.0 - 0.5), 0.5, new Lambertian(Vector3(0.8, 0.6, 0.2)));
//    list[4] = new Sphere(Vector3(0, 0, -1.0), -0.45, new Dielectric(Vector3(0.5, 0, 0), 1.5));
//    float radius = cos(M_PI / 4);
//    list[0] = new Sphere(Vector3(-radius, 0, -1.0), radius, new Lambertian(Vector3(1, 0, 0)));
//    list[1] = new Sphere(Vector3(radius, 0, -1.0), radius, new Lambertian(Vector3(0, 0, 1)));
//    Hitable *world = new HitableList(list, 4);
    
//    Hitable **list = new Hitable*[4];
//    list[0] = new Sphere(Vector3(0, 0, -1), 0.5, new Lambertian(Vector3(0.1, 0.2, 0.5)));
//    list[1] = new Sphere(Vector3(0, -100.5, -1), 100, new Lambertian(Vector3(0.8, 0.8, 0)));
//    list[2] = new Sphere(Vector3(1, 0, -1), 0.5, new Metal(Vector3(0.8, 0.6, 0.2), 0.5));
//    list[3] = new Sphere(Vector3(-1, 0, -1), 0.5, new Dielectric(Vector3(1, 1, 1), 1.5));
//    list[4] = new Sphere(Vector3(-1, 0, -1), -0.45, new Dielectric(Vector3(1, 1, 1), 1.5));
//    Hitable *world = new HitableList(list, 4);
    
    Hitable *world = getRandomScene();
    
    Vector3 cameraPosition = Vector3(13, 2, 3);
    Vector3 lookAt = Vector3(0, 0, 0);
    float focusDistance = 10.0;
    float aperture = 0.1;
    Camera camera = Camera(cameraPosition, lookAt, Vector3(0, 1, 0),  20, (float) width / height, aperture, focusDistance);
    
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            cout << "(i, j): (" << i << ", " << j << ")" << endl;
            
            Vector3 color = Vector3(0, 0, 0);
            
            for (int s = 0; s < numAliasingSamples; s++) {
                float u = ((float) i + drand48()) / width;
                float v = ((float) j + drand48()) / height;
                
                Ray r = camera.getRay(u, v);
                color += getColor(r, world, 0);
            }
            color = color / numAliasingSamples;
            color = Vector3(sqrt(color.x), sqrt(color.y), sqrt(color.z));
            file << (int)(color.x * 255.99) << " " << (int)(color.y * 255.99) << " " << (int)(color.z * 255.99) << endl;
        }
    }
    
    file.close();
    
    return 0;
}
