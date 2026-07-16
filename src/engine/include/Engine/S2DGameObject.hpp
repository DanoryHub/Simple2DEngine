//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ENGINE_S2DGAMEOBJECT_HPP
#define ENGINE_S2DGAMEOBJECT_HPP
#include <string>

struct SDL_Renderer;

class S2DGameObject {
protected:
    std::string objectName;

public:
    virtual ~S2DGameObject() = default;

    const std::string& getName() const;
    void setName(const std::string& name);

    virtual void Iterate(float deltaTime);
};


#endif //ENGINE_S2DGAMEOBJECT_HPP