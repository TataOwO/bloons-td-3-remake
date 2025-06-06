#include "hitboxes/OvalHitbox.hpp"

#include "hitboxes/CircularHitbox.hpp"
#include "hitboxes/RectangularHitbox.hpp"

#include "utility/functions.hpp"

#include <cmath>
#include <algorithm>

#include "constants/HITBOX.hpp"


namespace hitboxes {

OvalHitbox::OvalHitbox(const glm::vec2& center, const glm::vec2& radii, float rotation)
	: center(center), radii(radii), rotation(rotation) {
}

bool OvalHitbox::is_collided_with(std::shared_ptr<I_BaseHitbox> box) const {
	switch (box->get_type()) {
		case CONSTANTS::TYPE::HITBOX::CIRCULAR:
			return check_collision_circular(std::static_pointer_cast<CircularHitbox>(box));
		case CONSTANTS::TYPE::HITBOX::OVAL:
			return check_collision_oval(std::static_pointer_cast<OvalHitbox>(box));
		case CONSTANTS::TYPE::HITBOX::RECTANGULAR:
			return check_collision_rectangular(std::static_pointer_cast<RectangularHitbox>(box));
		default:
			return false; // this should never happen
	}
}

bool OvalHitbox::check_collision_circular(const std::shared_ptr<CircularHitbox>& other) const {
	// convert to local pos
	glm::vec2 local_circle_center = transform_to_local_space(other->get_position());
	
	glm::vec2 closest_on_unit_circle;
	if (glm::length(local_circle_center) < std::numeric_limits<float>::epsilon()) {
		// if the circle center is at rectangle center, pick an arbitrary point on the unit circle
		closest_on_unit_circle = glm::vec2(1.0f, 0.0f);
	} else {
		// otherwise, normalize to get closest point on unit circle
		closest_on_unit_circle = glm::normalize(local_circle_center);
	}
	
	// scale radii and get the closest point on the oval
	glm::vec2 closest_on_oval = glm::vec2(
		closest_on_unit_circle.x * radii.x,
		closest_on_unit_circle.y * radii.y
	);
	
	// transform back to world position
	glm::vec2 closest_world = transform_to_world_space(closest_on_oval);
	
	// check if point is inside the square
	float distance = glm::length(closest_world - other->get_position());
	return distance <= other->get_radius();
}

bool OvalHitbox::check_collision_oval(const std::shared_ptr<OvalHitbox>& other) const {
	// oval-oval approaximation, because real collision is too complex (i'm lazy 💀)
	
	// get number of sample points around each oval
	constexpr int NUM_SAMPLES = CONSTANTS::HITBOX::OVAL_SAMPLE_COUNT;
	
	// goes through each samples points of this oval, and check if they're inside of the other oval
	for (int i = 0; i < NUM_SAMPLES; i++) {
		float angle = 2.0f * static_cast<float>(M_PI) * static_cast<float>(i) / NUM_SAMPLES;
		glm::vec2 point_local = glm::vec2(
			std::cos(angle) * radii.x,
			std::sin(angle) * radii.y
		);
		glm::vec2 point_world = transform_to_world_space(point_local);
		
		if (other->contains_point(point_world)) {
			return true;
		}
	}
	
	// sample points in the other oval, and checks if they're inside this oval
	for (int i = 0; i < NUM_SAMPLES; i++) {
		float angle = 2.0f * static_cast<float>(M_PI) * static_cast<float>(i) / NUM_SAMPLES;
		glm::vec2 other_point_local = glm::vec2(
			std::cos(angle) * other->radii.x,
			std::sin(angle) * other->radii.y
		);
		glm::vec2 other_point_world = other->transform_to_world_space(other_point_local);
		
		if (contains_point(other_point_world)) {
			return true;
		}
	}
	
	return false;
}

bool OvalHitbox::check_collision_rectangular(const std::shared_ptr<RectangularHitbox>& other) const {
	throw std::invalid_argument("YOU MUST CALL COLLISION FROM RECTANGULAR HITBOX");
	return false;
}

bool OvalHitbox::contains_point(const glm::vec2& point) const {
	// transform to local space
	glm::vec2 local_point = transform_to_local_space(point);
	
	// get distance
	// (x/a)^2 + (y/b)^2 <= 1
	float normalized_x = local_point.x / radii.x;
	float normalized_y = local_point.y / radii.y;
	
	return (normalized_x * normalized_x + normalized_y * normalized_y) <= 1.0f;
}

glm::vec2 OvalHitbox::get_closest_point(const glm::vec2& point) const {
	// transform to local space
	glm::vec2 local_point = transform_to_local_space(point);
	
	// if point is at the center
	if (glm::length(local_point) < std::numeric_limits<float>::epsilon()) {
		// returns a point on the right edge of the oval
		return transform_to_world_space(glm::vec2(radii.x, 0.0f));
	}
	
	// this is an approaximation to reduce run time hazard
	// because there's no actual solution on this matter
	
	// get the direction of the point
	glm::vec2 direction = glm::normalize(local_point);
	
	// and scale it by radii
	glm::vec2 closest_on_oval = glm::vec2(
		direction.x * radii.x,
		direction.y * radii.y
	);
	
	// transform it back to real position
	return transform_to_world_space(closest_on_oval);
}

glm::vec2 OvalHitbox::transform_to_local_space(const glm::vec2& point) const {
	glm::vec2 centered = point - center;
	
	return utility::rotate_vec2(centered, -rotation);
}

glm::vec2 OvalHitbox::transform_to_world_space(const glm::vec2& point) const {
	// rotate it first
	glm::vec2 rotated = utility::rotate_vec2(point, rotation);
	
	// then translate it to world
	return rotated + center;
}

}
