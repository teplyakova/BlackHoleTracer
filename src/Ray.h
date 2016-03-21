#ifndef BLACK_HOLE_TRACER_RAY_H
#define BLACK_HOLE_TRACER_RAY_H

#include "glm/glm.hpp"

class Ray {
public:
    Ray(glm::vec3 in_start, glm::vec3 in_dir) : start(in_start),
                                                dir(glm::normalize(in_dir)),
                                                color(glm::vec3(0)),
                                                alpha(1) {}

public:
    glm::vec3 start;
    glm::vec3 dir;
    glm::vec3 color;
    float alpha;
};

#endif