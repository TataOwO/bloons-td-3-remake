#ifndef INTERFACE_BASE_HITBOX_HPP
#define INTERFACE_BASE_HITBOX_HPP

#include "CONSTANTS/TYPE.hpp"

namespace hitboxes {

class I_BaseHitbox {
public:
    virtual bool is_collided_with(std::shared_ptr<I_BaseHitbox> box) const = 0;
    
    virtual glm::vec2 get_position() const = 0;
    
    virtual void set_position(const glm::vec2& position) = 0;
    
    virtual float get_rotation() const = 0;
    
    virtual void set_rotation(float radians) = 0;
    
    virtual CONSTANTS::TYPE::HITBOX get_type() const = 0;
    
    virtual bool contains_point(const glm::vec2& point) const = 0;
    
    virtual glm::vec2 get_closest_point(const glm::vec2& point) const = 0;

public:
    virtual ~I_BaseHitbox() = default;
};

}

#endif
