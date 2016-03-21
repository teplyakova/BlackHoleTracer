#include "Scene.h"

Scene::Scene(const Config &config) :
    galaxy(ConfigHelper::safe_child(config, "galaxy")),
    infinity(ConfigHelper::safe_child(config, "stars")),
    sceneObjects(1)
{
    sceneObjects[0] = &galaxy;
}

void Scene::iterRay (Ray &ray, const vec3 &pos, const vec3 &delta) {
    vec4 color;

    for (BaseSceneObject *object : sceneObjects) {
        if (object -> intersect(pos, delta, &color)) {
            ray.color += ray.alpha * color.a * vec3(color);
            ray.alpha *= 1 - color.a;

            break;
        }
    }
}

vec3 Scene::countAcceleration(const vec3 &pos) {

    vec3 resultAcceleration;
    for (BaseSceneObject *object : sceneObjects) {
        resultAcceleration += object -> countAcceleration(pos);
    }

    return resultAcceleration;
}

vec3 Scene::getInfinityColor(const vec3 &dir) {
    return infinity.get_color(dir);
}
