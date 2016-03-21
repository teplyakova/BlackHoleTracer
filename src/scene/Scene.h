#ifndef BLACK_HOLE_TRACER_SCENE_H
#define BLACK_HOLE_TRACER_SCENE_H

#include "BaseSceneObject.h"
#include "Ray.h"
#include "Galaxy.h"
#include "SkySphere.h"
#include "config/Config.h"
#include "constants.h"

using std::vector;
using glm::vec3;
using glm::vec4;

class Scene {
public:
    Scene(const Config &config = Config());

    vec3 countAcceleration(const vec3 &pos);
    void iterRay(Ray& ray, const vec3 &pos, const vec3 &delta);
    vec3 getInfinityColor(const vec3 &dir);
private:
    Galaxy galaxy;

    SkySphere infinity;
    vector <BaseSceneObject*> sceneObjects;
};

#endif
