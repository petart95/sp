//
//  CreateMap.hpp
//  sp
//
//  Created by maxeler on 8/25/16.
//  Copyright © 2016 ptrifunovic. All rights reserved.
//

#ifndef CreateMap_hpp
#define CreateMap_hpp

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

#endif /* CreateMap_hpp */
