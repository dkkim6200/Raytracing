#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

class Hitable;

class HitableList : public Hitable {
private:
    int size;
    Hitable **list;
    
public:
    HitableList();
    HitableList(Hitable **list, int size);
    virtual bool hit(Ray r, HitRecord &hitRec);
};

#endif

