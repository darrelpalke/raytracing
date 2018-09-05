
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <string>
#include <algorithm>
#include <iostream>

#include "sphere.h"
#include "hittable_list.h"

using namespace std;

const int w = 1024;
const int h = 768;
const string outputFileName = "out.png";

void write_image(glm::vec4* pData)
{
    cout << "Converting image.\n" << endl;
    uint32_t* pOutData = new uint32_t[w * h];

    int offset = 0;
    for (int y = h - 1; y >= 0; y--)
    {
        for (int x = 0; x < w; x++)
        {
            uint32_t r = max(min((int)(255.0f * pData[y * w + x].r), 255), 0);
            uint32_t g = max(min((int)(255.0f * pData[y * w + x].g), 255), 0);
            uint32_t b = max(min((int)(255.0f * pData[y * w + x].b), 255), 0);
            uint32_t a = max(min((int)(255.0f * pData[y * w + x].a), 255), 0);
            pOutData[offset++] = r | (g << 8) | (b << 16) | (a << 24);
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

glm::vec4 color(const ray& r, hittable* world)
{
    hit_record rec;
    if (world->hit(r, 0.0f, FLT_MAX, rec))
    {
        glm::vec3 N = 0.5f * (rec.normal + glm::vec3(1.0f, 1.0f, 1.0f));
        return glm::vec4(N.x, N.y, N.z, 1.0f);
    }
    else
    {
        // otherwise set color based on y of normalized dir.
        glm::vec3 dir_normalized = glm::normalize(r.dir);
        float t = 0.5f * (dir_normalized.y + 1.0f);
        return (1.0f - t) * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) + t * glm::vec4(0.5f, 0.7f, 1.0f, 1.0f);
    }
}

int main(int argc, char** argv)
{
    glm::vec4* pData = new glm::vec4[w * h];

    float aspectRatio = (float)w / (float)h;

    glm::vec3 lowerleft(-aspectRatio, -1.0f, -1.0f);
    glm::vec3 horizontal(2.0f * aspectRatio, 0.0f, 0.0f);
    glm::vec3 vertical(0.0f, 2.0f, 0.0f);
    glm::vec3 origin(0.0f, 0.0f, 0.0f);

    vector<hittable*> list;
    list.push_back(new sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
    list.push_back(new sphere(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));

    hittable* world = new hittable_list(list);

    cout << "Ray tracing!!!\n" << endl;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            float u = (float)x / (float)w;
            float v = (float)y / (float)h;
            ray r(origin, lowerleft + u * horizontal + v * vertical);
            pData[y * w + x] = color(r, world);            
        }
        if ((y + 1) % 20 == 0)
        {
            cout << ".";
        }
    }
    cout << endl << endl;

    write_image(pData);

    delete world;
    delete pData;

    return 0;
}