#ifndef CREATEVECTOR_H
#define CREATEVECTOR_H

#include <vector>
#include <algorithm>

template <typename T>
class createVector
{
private:
    std::vector<T> vector;
public:
    createVector(const T& val) {
        vector.push_back(val);
    }
    
    createVector<T>& operator()(const T& val) {
        vector.push_back(val);
        return *this;
    }
    
    operator std::vector<T>() {
        return vector;
    }
};

template <typename T>
bool contains(std::vector<T> & v, T val) {
    return std::find(v.begin(), v.end(), val) != v.end();
}

#endif
