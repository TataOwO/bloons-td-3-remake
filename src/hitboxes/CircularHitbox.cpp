#include "hitboxes/CircularHitbox.hpp"

#include "hitboxes/OvalHitbox.hpp"
#include "hitboxes/RectangularHitbox.hpp"

namespace hitboxes {

CircularHitbox::CircularHitbox(const glm::vec2& center, float radius)
	: center(center), m_radius(radius), rotation(0.0f) {
}

bool CircularHitbox::is_collided_with(std::shared_ptr<I_BaseHitbox> box) const {
	switch (box->get_type()) {
		case CONSTANTS::TYPE::HITBOX::CIRCULAR:
			return check_collision_circular(std::static_pointer_cast<CircularHitbox>(box));
		case CONSTANTS::TYPE::HITBOX::OVAL:
			return check_collision_oval(std::static_pointer_cast<OvalHitbox>(box));
		case CONSTANTS::TYPE::HITBOX::RECTANGULAR:
			return check_collision_rectangular(std::static_pointer_cast<RectangularHitbox>(box));
		default:
			return false; // this sbould never happen
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
	// returns true if point is inside the circle
	float distance = glm::length(point - center);
	return distance <= m_radius;
}

glm::vec2 CircularHitbox::get_closest_point(const glm::vec2& point) const {
	glm::vec2 direction = point - center;
	
	// if point is at the center, returns the right edge
	if (glm::length(direction) < std::numeric_limits<float>::epsilon()) {
		return center + glm::vec2(m_radius, 0.0f);
	}
	
	// otherwise, normalize the direction and scale, and return the actually closest point
	return center + glm::normalize(direction) * m_radius;
}

}
