
#pragma once

#include "hittable.h"

class sphere : public hittable
{
public:
    sphere() {}
    sphere(glm::vec3 cen, float r) { center = cen; radius = r; }
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    glm::vec3 center;
    float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    glm::vec3 oc = r.pt - center;
    float a = glm::dot(r.dir, r.dir);
    float b = glm::dot(oc, r.dir);
    float c = dot(oc, oc) - radius * radius;
    float disc = b * b - a * c;
    if (disc > 0.0f)
    {
        float t = (-b - sqrt(disc)) / a;

        if (t > t_min && t < t_max)
        {
            rec.t = t;
            rec.p = r.point_at_parameter(t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }

        t = (-b + sqrt(disc)) / a;
        if (t > t_min && t < t_max)
        {
            rec.t = t;
            rec.p = r.point_at_parameter(t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}
