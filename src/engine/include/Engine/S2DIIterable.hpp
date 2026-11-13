//
// Created by IvanMiatselski on 29.07.2026.
//

#ifndef ARCANOID_S2DIITERABLE_HPP
#define ARCANOID_S2DIITERABLE_HPP

namespace S2D {

class IIterable {
public:
    virtual ~IIterable() {};
    virtual void Iterate(float deltaTime) = 0;
};

} // namespace S2D

#endif //ARCANOID_S2DIITERABLE_HPP
