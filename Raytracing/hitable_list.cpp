#include <iostream>
#include <cmath>

#include "vector3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "hitable_list.hpp"

HitableList::HitableList() {
    list = NULL;
    size = 0;
}

HitableList::HitableList(Hitable **list, int size) {
    this->list = list;
    this->size = size;
}

bool HitableList::hit(Ray r, HitRecord &hitRec) {
    bool didHit = false;
    float minDistanceSquared = HUGE_VALF;
    
    HitRecord tempHitRec;
    
    for (int i = 0; i < size; i++) {
        if (list[i]->hit(r, tempHitRec) &&
            minDistanceSquared > (r.getOrigin() - tempHitRec.pHit).getSquaredMag()) {
            
            didHit = true;
            minDistanceSquared = (r.getOrigin() - tempHitRec.pHit).getSquaredMag();
            hitRec = tempHitRec;
        }
    }
    
    return didHit;
}
