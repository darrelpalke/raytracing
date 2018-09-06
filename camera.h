
#pragma once

#include <cstdlib>
#include "ray.h"

float random()
{
    return (float)rand() / (float)RAND_MAX;
}

class camera
{
public:
    camera(int w, int h)
    {
        wd = w;
        ht = h;

        float aspectRatio = (float)w / (float)h;
        lower_left_corner = glm::vec3(-aspectRatio, -1.0f, -1.0f);
        horizontal = glm::vec3(2.0f * aspectRatio, 0.0f, 0.0f);
        vertical = glm::vec3(0.0f, 2.0f, 0.0f);
        origin = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    ray get_ray(int x, int y, bool antialiasRandom = false)
    {
        float u = ((float)x + (antialiasRandom ? random() : 0.0f)) / (float)wd;
        float v = ((float)y + (antialiasRandom ? random() : 0.0f)) / (float)ht;

        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

    int wd;
    int ht;
    glm::vec3 origin;
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
};