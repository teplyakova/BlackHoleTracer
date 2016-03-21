#ifndef BLACK_HOLE_TRACER_CAMERA_H
#define BLACK_HOLE_TRACER_CAMERA_H

#include "glm/glm.hpp"
#include "vector"
#include "constants.h"
#include "math.h"
#include "config/Config.h"

class Camera
{
public:
   Camera(const Config &config) : pos(ConfigHelper::get_vector(config, "camera_pos", CAMERA_POSITION)) {
       float alpha = glm::radians(config.get<float>("angle", VERTICAL_VIEW_ANGLE));

       resolution = ConfigHelper::get_vector(config, "resolution", RES_DEFAULT);

       right = glm::normalize(ConfigHelper::get_vector(config, "right", RIGHT)) * float(resolution.x);
       up = glm::normalize(ConfigHelper::get_vector(config, "up", UP)) * float(resolution.y);
       forward = glm::normalize(ConfigHelper::get_vector(config, "forward", FORWARD)) * ((float(resolution.y)/2) / tanf(alpha/2));

       pixels.resize(resolution.x * resolution.y);
   }
public:
    glm::vec3 pos;          // Camera position and orientation
    glm::vec3 forward;      // Orthonormal basis
    glm::vec3 right;
    glm::vec3 up;

    glm::uvec2 resolution;  // Image resolution: w, h
    std::vector<glm::vec3> pixels;  // Pixel array
};

#endif