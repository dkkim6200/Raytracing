#ifndef CAMERA_H
#define CAMERA_H

class Ray;

class Camera {
private:
    Vector3 bottomLeft;
    Vector3 horizontal;
    Vector3 vertical;
    Vector3 origin;
    
    Vector3 u, v, w;
    float lensRadius;
    
public:
    Camera(Vector3 position, Vector3 lookAt, Vector3 up, float fov, float aspect, float aperture, float focusDistance);
    Ray getRay(float u, float v);
};

#endif
