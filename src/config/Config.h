#ifndef BLACK_HOLE_TRACER_CONFIGMANAGER_H
#define BLACK_HOLE_TRACER_CONFIGMANAGER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>
#include <iostream>

using namespace boost::property_tree;
using std::string;

typedef boost::property_tree::ptree Config;

#define NAME_QUOTE (v) ##v

namespace ConfigHelper {
    template<typename T>
    std::vector<T> as_vector(Config const &pt, Config::key_type const &key);

    template<typename T>
    T get_vector(Config const &pt, Config::key_type const &key, const T defaultValue);

    Config safe_child(Config const &pt, Config::key_type const &key);
}

//Include realisation of template functions
#include "Config.tcc"

#endif //BLACK_HOLE_TRACER_CONFIGMANAGER_H
