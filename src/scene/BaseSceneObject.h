#ifndef BLACK_HOLE_TRACER_BASESCENEOBJECT_H
#define BLACK_HOLE_TRACER_BASESCENEOBJECT_H

#include "glm/glm.hpp"

using glm::vec3;
using glm::vec4;

class BaseSceneObject {
public:
    virtual bool intersect(const vec3 &pos, const vec3 &delta, vec4 *intersectionColor) {return false;}
    virtual vec3 countAcceleration(const vec3 &pos) {return vec3 ();}
};


#endif //BLACK_HOLE_TRACER_BASESCENEOBJECT_H
