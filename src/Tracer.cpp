#include "Tracer.h"
#include "Ray.h"
#include "glm/gtx/intersect.hpp"
#include "glm/glm.hpp"
#include "omp.h"

using namespace glm;

Tracer::Tracer(const Config &config) :
    camera(config),
    scene(ConfigHelper::safe_child(config, "scene")),
    maxIter(config.get<int>("max_iterations", MAX_ITER)),
    delta(config.get<float>("delta", DELTA))
{}

Ray Tracer::MakeRay(uvec2 pixelPos)
{
    vec2 pos(pixelPos);
    vec2 resolution(camera.resolution);
    vec2 temp = (pos + vec2(0.5f))/resolution - vec2(0.5f);

    auto start = camera.pos;
    auto dir = camera.forward + temp.x * camera.right + temp.y * camera.up;
    return Ray(start, dir);
}

glm::vec3 Tracer::TraceRay(Ray ray) {
    vec3 pos = camera.pos;
    vec3 vel0 = LIGHT_VELOCITY * ray.dir;
    vec3 acc, norm_acc, vel = vel0;
    vec3 displ(0);
    vec4 color;
    float t;
    float alpha;

    int iter = 0;

    while (iter < maxIter) {
        acc = scene.countAcceleration(pos);
        norm_acc = acc - dot(acc, ray.dir) * ray.dir;
        vel = vel0 + delta * norm_acc;
        displ = delta * vel0 + norm_acc * (delta * delta / 2);

        scene.iterRay(ray, pos, displ);

        if (ray.alpha < FLT_EPSILON) {
            //Change to break?
            return ray.color;
        }

        pos += displ;
        vel0 = vel;
        ray.dir = normalize(vel);
        iter++;
    }

    //get color from stars
    return ray.color + ray.alpha * scene.getInfinityColor(ray.dir);
}

void Tracer::RenderImage()
{
    unsigned xRes = camera.resolution.x;
    unsigned yRes = camera.resolution.y;

    // Rendering
    #pragma omp parallel for
    for (unsigned i = 0; i < yRes; i++) {
        for (unsigned j = 0; j < xRes; j++) {
            Ray ray = MakeRay(uvec2(j, i));
            camera.pixels[i * xRes + j] = TraceRay(ray);
        }
    }
}

void Tracer::SaveImageToFile(std::string fileName)
{
    int width = camera.resolution.x;
    int height = camera.resolution.y;

    CImage image(width, height, 1, 4);

    int textureDisplacement = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            vec3 color = camera.pixels[textureDisplacement + j];
            image(j, i, 0) = clamp(color.r, 0.0f, 255.0f);
            image(j, i, 1) = clamp(color.g, 0.0f, 255.0f);
            image(j, i, 2) = clamp(color.b, 0.0f, 255.0f);
            image(j, i, 3) = 255;
        }
        textureDisplacement += width;
    }
    image.save(fileName.c_str());
}
