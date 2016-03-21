#ifndef BLACK_HOLE_TRACER_TRACER_H
#define BLACK_HOLE_TRACER_TRACER_H

#include "glm/glm.hpp"
#include <string>
#include "Ray.h"
#include "Camera.h"
#include "scene/Scene.h"
#include "config/Config.h"

#include "CImg/CImg.h"

typedef cimg_library::CImg<unsigned char> CImage;

class Tracer {
public:
    Tracer(const Config &config = Config());
    Ray MakeRay(glm::uvec2 pixelPos);  // Create ray for specified pixel
    glm::vec3 TraceRay(Ray ray); // Trace ray, compute its color
    void RenderImage();
    void SaveImageToFile(std::string fileName);
private:
    int maxIter;
    float delta;

    Camera camera;
    Scene scene;
};


#endif
