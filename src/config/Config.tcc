#include "Config.h"

template<typename T>
std::vector<T> ConfigHelper::as_vector(Config const &pt, Config::key_type const &key) {
    if (pt.count(key) == 0) return std::vector<T>();

    std::vector<T> r;
    for (auto &item : pt.get_child(key))
        r.push_back(item.second.get_value<T>());
    return r;
}

template<typename T>
T ConfigHelper::get_vector(Config const &pt, Config::key_type const &key, const T defaultValue) {
    std::vector<typename T::value_type> vector;
    vector = as_vector<typename T::value_type>(pt, key);

    T result = defaultValue;

    if (vector.size() != result.length()) return result;

    for (int i = 0; i < vector.size(); i ++) {
        result[i] = vector[i];
    }

    return result;
}