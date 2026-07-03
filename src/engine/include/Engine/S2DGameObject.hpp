//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ARCANOID_S2DGAMEOBJECT_HPP
#define ARCANOID_S2DGAMEOBJECT_HPP
#include <string>

class S2DGameObject {
protected:
    std::string objectName;
public:
    virtual ~S2DGameObject() = default;
    std::string getName() const;
    void setName(const std::string name);
    virtual void Iterate(float deltaTime);
};


#endif //ARCANOID_S2DGAMEOBJECT_HPP