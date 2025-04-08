#ifndef CIRCULAR_HITBOX_HPP
#define CIRCULAR_HITBOX_HPP

#include "hitboxes/I_BaseHitbox.hpp"
#include "hitboxes/OvalHitbox.hpp"
#include "hitboxes/RectangularHitbox.hpp"

namespace hitboxes {

class CircularHitbox : public I_BaseHitbox {
public:
	CircularHitbox(const glm::vec2& center, float radius);
	
	CircularHitbox(const CircularHitbox&) = delete;

	CircularHitbox(CircularHitbox&&) = delete;

	CircularHitbox& operator=(const CircularHitbox&) = delete;

	CircularHitbox& operator=(CircularHitbox&&) = delete;

	~CircularHitbox() = default;

	// collision detection
	bool is_collided_with(std::shared_ptr<I_BaseHitbox> box) const override;
	bool check_collision_circular(const std::shared_ptr<CircularHitbox>& other) const;
	bool check_collision_oval(const std::shared_ptr<class OvalHitbox>& other) const;
	bool check_collision_rectangular(const std::shared_ptr<class RectangularHitbox>& other) const;
	
	// Position methods
	glm::vec2 get_position() const override { return center; }
	void set_position(const glm::vec2& position) override { center = position; }
	
	// position
	float get_rotation() const override { return rotation; }
	void set_rotation(float radians) override { rotation = radians; }
	
	// hitbox type
	HitboxType get_type() const override { return HitboxType::CIRCULAR; }
	
	// points
	bool contains_point(const glm::vec2& point) const override;
	glm::vec2 get_closest_point(const glm::vec2& point) const override;
	
	// radius
	float get_radius() const { return m_radius; }
	void  set_radius(float radius) {m_radius=radius;}
private:
	glm::vec2 center;
	float m_radius;
	float rotation;

};

};

#endif
