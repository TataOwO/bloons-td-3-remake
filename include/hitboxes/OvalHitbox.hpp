#ifndef OVAL_HITBOX_HPP
#define OVAL_HITBOX_HPP

#include "hitboxes/I_BaseHitbox.hpp"
#include "hitboxes/CircularHitbox.hpp"

namespace hitboxes {

class OvalHitbox final : public I_BaseHitbox {
public:
	// Constructor
	OvalHitbox(const glm::vec2& center, const glm::vec2& radii, float rotation = 0.0f);

	// Collision detection methods
	bool is_collided_with(std::shared_ptr<I_BaseHitbox> box) const override;
	bool check_collision_circular(const std::shared_ptr<class CircularHitbox>& other) const;
	bool check_collision_oval(const std::shared_ptr<OvalHitbox>& other) const;
	bool check_collision_rectangular(const std::shared_ptr<class RectangularHitbox>& other) const;

	// Position methods
	glm::vec2 get_position() const override { return center; }
	void set_position(const glm::vec2& position) override { center = position; }

	// Rotation methods
	float get_rotation() const override { return rotation; }
	void set_rotation(float radians) override { rotation = radians; }

	// Type getter
	HitboxType get_type() const override { return HitboxType::OVAL; }

	// Point methods
	bool contains_point(const glm::vec2& point) const override;
	glm::vec2 get_closest_point(const glm::vec2& point) const override;

	// Specific getters for this shape
	glm::vec2 get_radii() const { return radii; }

	// Helper methods
	glm::vec2 transform_to_local_space(const glm::vec2& point) const;
	glm::vec2 transform_to_world_space(const glm::vec2& point) const;
private:

	glm::vec2 center;	  // Center position of the oval
	glm::vec2 radii;	   // X and Y radii (semi-major and semi-minor axes)
	float rotation;		// Rotation in radians (counter-clockwise)

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
