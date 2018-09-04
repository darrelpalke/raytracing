
#pragma once

#include "glm\glm.hpp"

class ray
{
public:
    ray() {}
    ray(const glm::vec3& pt, const glm::vec3& dir) { this->pt = pt; this->dir = dir; }
    glm::vec3 point_at_parameter(float t) const { return pt + t * dir; }

    glm::vec3 pt, dir;
};
