#ifndef BLACK_HOLE_TRACER_TEXTURE_H
#define BLACK_HOLE_TRACER_TEXTURE_H

#include "glm/glm.hpp"
#include <vector>
#include <stdint.h>
#include <string>

#include "CImg/CImg.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
typedef cimg_library::CImg<unsigned char> CImage;

class Texture {
public:
    Texture () :
        width (0),
        height(0),

        pixels()
    {}

    bool load (std::string name) {
        try {
            CImage img(name.c_str ());

            width = img.width();
            height = img.height();

            int channels = img.spectrum ();

            for (int i = 0; i < img.height(); i++) {
                for (int j = 0; j < img.width(); j++) {
                    uint8_t r = img(j, i, 0);
                    uint8_t g = img(j, i, 1);
                    uint8_t b = img(j, i, 2);

                    uint8_t a = 255;
                    if (channels > 3) a = img(j, i, 3);

                    pixels.push_back(vec4(r, g, b, a / 255.0f));
                }
            }
        }
        catch (cimg_library::CImgIOException) {
            return false;
        }

        return true;
    }

    vec4 getColor (int x, int y) {
        return pixels[y * width + x];
    }

    vec4 getFromSphereCoord (vec3 dir) {
        float x, y, z;
        x = dir.x;
        y = dir.y;
        z = dir.z;

        float phi = atan2f(y, x);
        float theta = asinf(z);

        int xp = int(glm::clamp(float((phi + M_PI) / 2 / M_PI * width), 0.0f, float(width-1)));
        int yp = int(glm::clamp(float(((theta + M_PI/2) / M_PI) * height), 0.0f, float(height-1)));

        return getColor(xp, yp);
    }

    vec4 getFromTextureCoord (float x, float y) {
        x -= (long)x;
        y -= (long)y;
        return getColor((int)(x * width), (int)(y * height));
    }

private:
    int width;
    int height;
    std::vector<vec4> pixels;
};

#endif //BLACK_HOLE_TRACER_TEXTURE_H
