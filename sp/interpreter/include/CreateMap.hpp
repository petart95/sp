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
bool contains(std::map<T, U> & map, T key) {
    return map.find(key) != map.end();
}

template <typename T, typename U>
bool containsVal(std::map<T, U> & map, U val) {
    typename std::map<T, U>::const_iterator it;
    for (it = map.begin(); it != map.end(); ++it) {
        if (it->second == val) {
            return true;
        }
    }

    return false;
}

template <typename T, typename U>
T findByVal(std::map<T, U> & map, U val) {
    typename std::map<T, U>::const_iterator it;
    for (it = map.begin(); it != map.end(); ++it) {
        if (it->second == val) {
            return it->first;
        }
    }
}

#endif
