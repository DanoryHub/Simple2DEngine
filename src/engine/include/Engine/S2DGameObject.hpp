//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ENGINE_S2DGAMEOBJECT_HPP
#define ENGINE_S2DGAMEOBJECT_HPP

#include "Engine/S2DIIterable.hpp"

#include <string>

namespace S2D {

class GameObject: public S2D::IIterable {
protected:
    std::string objectName;

public:
    ~GameObject() override = default;

    const std::string& getName() const;
    void setName(const std::string& name);

    void Iterate(float deltaTime) override;
};

} // namespace S2D

#endif //ENGINE_S2DGAMEOBJECT_HPP
