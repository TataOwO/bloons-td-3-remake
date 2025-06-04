#ifndef RECTANGULAR_HITBOX_HPP
#define RECTANGULAR_HITBOX_HPP

#include "hitboxes/I_BaseHitbox.hpp"

namespace hitboxes {

class RectangularHitbox : public I_BaseHitbox {
public:
	RectangularHitbox(const glm::vec2& center, const glm::vec2& dimensions, float rotation = 0.0f);

	// collision detection
	bool is_collided_with(std::shared_ptr<I_BaseHitbox> box) const override;
	bool check_collision_circular(const std::shared_ptr<class CircularHitbox>& other) const;
	bool check_collision_oval(const std::shared_ptr<class OvalHitbox>& other) const;
	bool check_collision_rectangular(const std::shared_ptr<RectangularHitbox>& other) const;
	
	// position getter/setter
	glm::vec2 get_position() const override { return center; }
	void set_position(const glm::vec2& position) override { center = position; }
	
	// rotation getter/setter
	float get_rotation() const override { return rotation; }
	void set_rotation(float radians) override { rotation = radians; }
	
	// get type
	CONSTANTS::TYPE::HITBOX get_type() const override { return CONSTANTS::TYPE::HITBOX::RECTANGULAR; }
	
	// point getter/setter
	bool contains_point(const glm::vec2& point) const override;
	glm::vec2 get_closest_point(const glm::vec2& point) const override;
	
	// ratio
	glm::vec2 get_dimensions() const { return dimensions; }
	
	// other helper methods
	std::array<glm::vec2, 4> get_corners() const;
	glm::vec2 transform_to_local_space(const glm::vec2& point) const;
	glm::vec2 transform_to_world_space(const glm::vec2& point) const;
private:
	glm::vec2 center;
	glm::vec2 dimensions;
	float rotation;

// base
public:
	RectangularHitbox(const RectangularHitbox&) = delete;

	RectangularHitbox(RectangularHitbox&&) = delete;

	RectangularHitbox& operator=(const RectangularHitbox&) = delete;

	RectangularHitbox& operator=(RectangularHitbox&&) = delete;

	~RectangularHitbox() override = default;
};

}

#endif
