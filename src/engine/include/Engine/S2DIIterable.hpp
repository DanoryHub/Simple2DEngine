//
// Created by IvanMiatselski on 29.07.2026.
//

#ifndef ARCANOID_S2DIITERABLE_HPP
#define ARCANOID_S2DIITERABLE_HPP

class S2DIIterable {
public:
    virtual ~S2DIIterable() {};
    virtual void Iterate(float deltaTime) = 0;
};

#endif //ARCANOID_S2DIITERABLE_HPP