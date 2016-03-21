#ifndef BLACK_HOLE_TRACER_CONSTANTS_H
#define BLACK_HOLE_TRACER_CONSTANTS_H

#include "glm/glm.hpp"

const float LIGHT_VELOCITY = 3e8f;
const float GRAVITY_CONST = 6.674e-11f;

//default parameters for hole
const float BLACK_HOLE_MASS = 8.57e36f;
const float RATIO = 7;

//default parameters for image
const glm::uvec2 RES_DEFAULT = glm::uvec2 (800, 480);

const glm::vec3 CAMERA_POSITION = glm::vec3 (2e11f, 0, -1e10f);
const float VERTICAL_VIEW_ANGLE = 60; //in degrees
const glm::vec3 UP = glm::vec3(0, 0, 1);
const glm::vec3 FORWARD = glm::vec3(-1, 0, 0);
const glm::vec3 RIGHT = glm::vec3(0, 1, 0);

//default iterations
const int MAX_ITER = 1000;

//default time delta
const float DELTA = 1;

#endif