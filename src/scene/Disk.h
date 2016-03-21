#ifndef BLACK_HOLE_TRACER_DISK_H
#define BLACK_HOLE_TRACER_DISK_H

#include "glm/glm.hpp"
#include <vector>
#include <stdint.h>

#include "BaseSceneObject.h"
#include "constants.h"
#include "Texture.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;

class Disk : public BaseSceneObject {
public:
    Disk(const Config &config = Config()) :
        radius(config.get<float>("radius", 2.0f * GRAVITY_CONST * BLACK_HOLE_MASS / LIGHT_VELOCITY / LIGHT_VELOCITY * RATIO))
    {
        texture.load (config.get<string>("texture", "error.png"));
    }

    virtual bool intersect(const vec3 &pos, const vec3 &delta, vec4 *intersectionColor) {
        //Disk can be created only in center

        if (fabsf(delta.z) > FLT_EPSILON) {
            float t = -pos.z / delta.z;
            if ((t > -FLT_EPSILON) && (t < 1 + FLT_EPSILON)) {
                vec3 temp = pos + t * delta;
                vec2 intersection_pos = vec2(temp.x, temp.y);

                float x = intersection_pos.x;
                float y = intersection_pos.y;

                //get color from texture
                if ((fabsf(x) < radius + FLT_EPSILON) && (fabsf(y) < radius + FLT_EPSILON)) {
                    *intersectionColor = texture.getFromTextureCoord((x/radius + 1) / 2, (y/radius + 1) / 2);

                    return true;
                }
            }
        }

        return false;
    }

    float getRadius() const {
        return radius;
    }

    void setRadius(float radius) {
        Disk::radius = radius;
    }

private:
    Texture texture;
    float radius;
};

#endif