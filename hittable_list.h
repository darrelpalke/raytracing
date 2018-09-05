
#pragma once

#include "hittable.h"
#include <vector>

using namespace std;

class hittable_list : public hittable
{
public:
    hittable_list() {}
    hittable_list(vector<hittable*>& l) { list = l; }
    ~hittable_list();
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    vector<hittable*> list;
};

hittable_list::~hittable_list()
{
    for (auto hittable : list)
    {
        delete hittable;
    }
}

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;
    for (auto& hittable : list)
    {
        if (hittable->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
