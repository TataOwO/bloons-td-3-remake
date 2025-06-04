#ifndef OVAL_HITBOX_HPP
#define OVAL_HITBOX_HPP

#include "hitboxes/I_BaseHitbox.hpp"

namespace hitboxes {

class OvalHitbox final : public I_BaseHitbox {
public:
	OvalHitbox(const glm::vec2& center, const glm::vec2& radii, float rotation = 0.0f);

	// collision detection
	bool is_collided_with(std::shared_ptr<I_BaseHitbox> box) const override;
	bool check_collision_circular(const std::shared_ptr<class CircularHitbox>& other) const;
	bool check_collision_oval(const std::shared_ptr<OvalHitbox>& other) const;
	bool check_collision_rectangular(const std::shared_ptr<class RectangularHitbox>& other) const;

	// position getter/setter
	glm::vec2 get_position() const override { return center; }
	void set_position(const glm::vec2& position) override { center = position; }

	// rotation getter/setter
	float get_rotation() const override { return rotation; }
	void set_rotation(float radians) override { rotation = radians; }

	// hitbox type
	CONSTANTS::TYPE::HITBOX get_type() const override { return CONSTANTS::TYPE::HITBOX::OVAL; }

	// point methods
	bool contains_point(const glm::vec2& point) const override;
	glm::vec2 get_closest_point(const glm::vec2& point) const override;

	// ratio
	glm::vec2 get_radii() const { return radii; }

	// other helper methods
	glm::vec2 transform_to_local_space(const glm::vec2& point) const;
	glm::vec2 transform_to_world_space(const glm::vec2& point) const;
private:

	glm::vec2 center;
	glm::vec2 radii;
	float rotation;

// base
public:

	OvalHitbox(const OvalHitbox&) = delete;

	OvalHitbox(OvalHitbox&&) = delete;

	OvalHitbox& operator=(const OvalHitbox&) = delete;

	OvalHitbox& operator=(OvalHitbox&&) = delete;

	~OvalHitbox() override = default;
};

}

#endif
