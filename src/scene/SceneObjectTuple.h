#ifndef BLACK_HOLE_TRACER_SCENEOBJECTTUPLE_H
#define BLACK_HOLE_TRACER_SCENEOBJECTTUPLE_H

#include "glm/glm.hpp"
#include "config/Config.h"
#include "BaseSceneObject.h"

using glm::vec3;
using glm::vec4;

using std::string;

template <typename T1, typename T2>
class SceneObjectTuple : public BaseSceneObject {
public:
    SceneObjectTuple (const Config &config = Config(), const string &first_name = "first", const string &second_name = "second") :
        first  (ConfigHelper::safe_child(config, first_name)),
        second (ConfigHelper::safe_child(config, second_name))
    {}

    virtual bool intersect(const vec3 &pos, const vec3 &delta, vec4 *intersectionColor) {
        return first.intersect(pos, delta, intersectionColor) || second.intersect(pos, delta, intersectionColor);
    }
    virtual vec3 countAcceleration(const vec3 &pos) {
        return first.countAcceleration(pos) + second.countAcceleration(pos);
    }

protected:
    T1 first;
    T2 second;
};

#endif //BLACK_HOLE_TRACER_SCENEOBJECTTUPLE_H
