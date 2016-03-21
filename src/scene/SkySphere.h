#ifndef BLACK_HOLE_TRACER_STARS_H
#define BLACK_HOLE_TRACER_STARS_H

#include "glm/glm.hpp"
#include <vector>
#include <iostream>
#include "CImg/CImg.h"
#include <math.h>

#include "Texture.h"

class SkySphere {
public:
    SkySphere(const Config &config = Config()) {
        texture.load(config.get<string>("texture", "error.png"));
    }

    glm::vec3 get_color(glm::vec3 dir) {
        return vec3 (texture.getFromSphereCoord(dir));
    }

private:
    Texture texture;
};

#endif