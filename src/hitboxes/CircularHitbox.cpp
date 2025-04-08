#include "hitboxes/CircularHitbox.hpp"

#include <exception>
#include <cmath>
#include <algorithm>

// generated by Claude Sonnet 3.7
// but I reviewed it and confirmed it should work fine

namespace hitboxes {

CircularHitbox::CircularHitbox(const glm::vec2& center, float radius)
	: center(center), m_radius(radius), rotation(0.0f) {
}

bool CircularHitbox::is_collided_with(std::shared_ptr<I_BaseHitbox> box) const {
	switch (box->get_type()) {
		case HitboxType::CIRCULAR:
			return check_collision_circular(std::static_pointer_cast<CircularHitbox>(box));
		case HitboxType::OVAL:
			return check_collision_oval(std::static_pointer_cast<OvalHitbox>(box));
		case HitboxType::RECTANGULAR:
			return check_collision_rectangular(std::static_pointer_cast<RectangularHitbox>(box));
		default:
			return false;
	}
}

bool CircularHitbox::check_collision_circular(const std::shared_ptr<CircularHitbox>& other) const {
	float distance = glm::length(center - other->center);
	float combined_radii = m_radius + other->get_radius();
	return distance <= combined_radii;
}

bool CircularHitbox::check_collision_oval(const std::shared_ptr<OvalHitbox>& other) const {
    throw std::invalid_argument("YOU MUST CALL COLLISION FROM OVAL HITBOX");
	return 0;
}

bool CircularHitbox::check_collision_rectangular(const std::shared_ptr<RectangularHitbox>& other) const {
    throw std::invalid_argument("YOU MUST CALL COLLISION FROM RECTANGULAR HITBOX");
	return 0;
}

bool CircularHitbox::contains_point(const glm::vec2& point) const {
	// A point is inside a circle if its distance to the center is less than or equal to the radius
	float distance = glm::length(point - center);
	return distance <= m_radius;
}

glm::vec2 CircularHitbox::get_closest_point(const glm::vec2& point) const {
	glm::vec2 direction = point - center;
	
	// If point is at the center, return a point on the right edge
	if (glm::length(direction) < std::numeric_limits<float>::epsilon()) {
		return center + glm::vec2(m_radius, 0.0f);
	}
	
	// Normalize the direction and scale by radius to get the closest point on the circle
	return center + glm::normalize(direction) * m_radius;
}

}
