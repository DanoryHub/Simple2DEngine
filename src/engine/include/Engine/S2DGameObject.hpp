//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ENGINE_S2DGAMEOBJECT_HPP
#define ENGINE_S2DGAMEOBJECT_HPP
#include "Engine/S2DIIterable.hpp"
#include <string>

class S2DGameObject: public S2DIIterable {
protected:
    std::string objectName;

public:
    ~S2DGameObject() override = default;

    const std::string& getName() const;
    void setName(const std::string& name);

    void Iterate(float deltaTime) override;
};


#endif //ENGINE_S2DGAMEOBJECT_HPP