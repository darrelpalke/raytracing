
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "glm\glm.hpp"

#include <string>
#include <algorithm>
#include <iostream>

#include "ray.h"

using namespace std;

const int w = 1024;
const int h = 768;
const string outputFileName = "out.png";

void write_image(glm::vec4* pData)
{
    cout << "Converting image.\n" << endl;
    uint32_t* pOutData = new uint32_t[w * h];
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            uint32_t r = max(min((int)(255.0f * pData[y * w + x].r), 255), 0);
            uint32_t g = max(min((int)(255.0f * pData[y * w + x].g), 255), 0);
            uint32_t b = max(min((int)(255.0f * pData[y * w + x].b), 255), 0);
            uint32_t a = max(min((int)(255.0f * pData[y * w + x].a), 255), 0);
            pOutData[y * w + x] = r | (g << 8) | (b << 16) | (a << 24);
        }

        if ((y + 1) % 20 == 0)
        {
            cout << ".";
        }
    }
    cout << endl << endl;

    cout << "Outputted image to " << outputFileName << ".\n" << endl;
    stbi_write_png(outputFileName.c_str(), w, h, 4, pOutData, 0);
    delete pOutData;
}

bool hit_sphere(const glm::vec3& center, float radius, const ray& r)
{
    glm::vec3 oc = r.pt - center;
    float a = glm::dot(r.dir, r.dir);
    float b = 2.0f * glm::dot(oc, r.dir);
    float c = dot(oc, oc) - radius * radius;
    float disc = b * b - 4 * a * c;
    return disc > 0.0f;
}

glm::vec4 color(const ray& r)
{
    if (hit_sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r))
    {
        return glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    glm::vec3 dir_normalized = glm::normalize(r.dir);
    float t = 0.5f * (dir_normalized.y + 1.0f);
    return (1.0f - t) * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) + t * glm:: vec4(0.5f, 0.7f, 1.0f, 1.0f);
}

int main(int argc, char** argv)
{
    glm::vec4* pData = new glm::vec4[w * h];

    //for (int y = 0; y < h; y++)
    //{
    //    for (int x = 0; x < w; x++)
    //    {
    //        glm::vec4 v;
    //        v.r = (float)x / (float)w;
    //        v.g = (float)y / (float)h;
    //        v.b = 0.2f;
    //        v.a = 1.0f;
    //        pData[y * w + x] = v;
    //    }
    //}

    float aspectRatio = (float)w / (float)h;

    glm::vec3 lowerleft(-aspectRatio, -1.0f, -1.0f);
    glm::vec3 horizontal(2.0f * aspectRatio, 0.0f, 0.0f);
    glm::vec3 vertical(0.0f, 2.0f, 0.0f);
    glm::vec3 origin(0.0f, 0.0f, 0.0f);

    cout << "Ray tracing!!!\n" << endl;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            float u = (float)x / (float)w;
            float v = (float)y / (float)h;
            ray r(origin, lowerleft + u * horizontal + v * vertical);
            pData[y * w + x] = color(r);            
        }
        if ((y + 1) % 20 == 0)
        {
            cout << ".";
        }
    }
    cout << endl << endl;

    write_image(pData);

    delete pData;

    cout << "Press enter to exit!" << endl;
    int a = getchar();

    return 0;
}