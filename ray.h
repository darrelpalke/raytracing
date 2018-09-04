
#pragma once

#include "glm\glm.hpp"

class ray
{
public:
    ray() {}
    ray(const glm::vec3& pt, const glm::vec3& dir) { Pt = pt; Dir = dir; }
    glm::vec3 origin() { return Pt; }
    glm::vec3 direction() { return Dir; }
    glm::vec3 point_at_parameter(float t) { return Pt + t * Dir; }

    glm::vec3 Pt, Dir;
};
