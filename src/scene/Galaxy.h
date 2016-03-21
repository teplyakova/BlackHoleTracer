#ifndef BLACK_HOLE_TRACER_GALAXY_H
#define BLACK_HOLE_TRACER_GALAXY_H

#include "SceneObjectTuple.h"
#include "BlackHole.h"
#include "Disk.h"

class Galaxy : public SceneObjectTuple <BlackHole, Disk> {
public:
    Galaxy(const Config &config = Config()) :
        SceneObjectTuple(config, "", "")
    {
        second.setRadius(first.getRadius() * config.get<float>("ratio", RATIO));
    }
};

#endif //BLACK_HOLE_TRACER_GALAXY_H
