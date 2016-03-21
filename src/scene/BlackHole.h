#ifndef BLACK_HOLE_TRACER_BLACK_HOLE_H
#define BLACK_HOLE_TRACER_BLACK_HOLE_H

#include "glm/glm.hpp"
#include "glm/gtx/intersect.hpp"

#include "config/Config.h"
#include "constants.h"

#include "BaseSceneObject.h"

using glm::vec3;
using glm::vec4;

class BlackHole : public BaseSceneObject {
public:
    BlackHole(const Config &config = Config()) :
        mass(config.get<float>("mass", BLACK_HOLE_MASS))
    {
        radius = 2 * GRAVITY_CONST / LIGHT_VELOCITY / LIGHT_VELOCITY * mass;
    }

    virtual bool intersect(const vec3 &pos, const vec3 &delta, vec4 *intersectionColor) {
        //Black hole can be created only in center
        const vec3 position = vec3(0, 0, 0);

        if (intersects (pos, delta, position)) {
            *intersectionColor = vec4(0, 0, 0, 1);
            return true;
        }

        return false;
    }
    bool intersects(const vec3 &pos, const vec3 &delta, const vec3 &position) {
        float intersect_dist = 0;
        bool intersection = glm::intersectRaySphere(pos, glm::normalize(delta), position, radius*radius, intersect_dist);

        return intersection && intersect_dist < glm::length(delta) + FLT_EPSILON;
    }

    virtual vec3 countAcceleration(const vec3 &pos) {
        float r = glm::length(pos);
        return (-GRAVITY_CONST * mass / r / r /r) * pos;
    }

    float getMass() const {
        return mass;
    }

    void setMass(float mass) {
        BlackHole::mass = mass;
    }
    float getRadius() const {
        return radius;
    }

    void setRadius(float radius) {
        BlackHole::radius = radius;
    }

private:
    float mass;
    float radius;
};

#endif
