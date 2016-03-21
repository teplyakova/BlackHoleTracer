#include "Config.h"

Config ConfigHelper::safe_child(Config const &pt, Config::key_type const &key) {
    if (key == "")          return pt;
    if (pt.count(key) == 0) return Config();
    return pt.get_child (key);
}