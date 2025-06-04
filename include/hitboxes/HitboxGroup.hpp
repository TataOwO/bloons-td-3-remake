#ifndef HITBOXES_GROUP_HPP
#define HITBOXES_GROUP_HPP

#include "hitboxes/I_BaseHitbox.hpp"

namespace hitboxes {

class HitboxGroup final : public I_BaseHitbox {
public:
	HitboxGroup() = default;

    bool is_collided_with(std::shared_ptr<I_BaseHitbox> box) const override; // IMPLEMENT

    CONSTANTS::TYPE::HITBOX get_type() const override {return CONSTANTS::TYPE::HITBOX::GROUPED;};

    bool contains_point(const glm::vec2& point) const override;
	
	// hitboxes setters
	void add_hitboxes(const std::vector<std::shared_ptr<I_BaseHitbox>>&);
	void clear_hitboxes() {m_hitboxes.clear();}

	// non implementation functions
    glm::vec2 get_position() const override {return glm::vec2{0,0};}
    void set_position(const glm::vec2& position) override {}
    float get_rotation() const override {return 0;};
    void set_rotation(float radians) override {};
    glm::vec2 get_closest_point(const glm::vec2& point) const override {return glm::vec2{0,0};};

private:
	std::vector<std::shared_ptr<I_BaseHitbox>> m_hitboxes = {};

public:
	HitboxGroup(const HitboxGroup&) = delete;

	HitboxGroup(HitboxGroup&&) = delete;

	HitboxGroup& operator=(const HitboxGroup&) = delete;

	HitboxGroup& operator=(HitboxGroup&&) = delete;

	~HitboxGroup() override = default;
};

}

#endif
