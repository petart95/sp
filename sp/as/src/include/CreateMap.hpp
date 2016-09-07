#ifndef CREATEMAP_H
#define CREATEMAP_H

#include <map>

template <typename T, typename U>
class createMap
{
private:
    std::map<T, U> map;
public:
    createMap(const T& key, const U& val) {
        map[key] = val;
    }
    
    createMap<T, U>& operator()(const T& key, const U& val) {
        map[key] = val;
        return *this;
    }
    
    operator std::map<T, U>() {
        return map;
    }
};

template <typename T, typename U>
bool contains(std::map<T, U> & map, T val) {
    return map.find(val) != map.end();
}

#endif
