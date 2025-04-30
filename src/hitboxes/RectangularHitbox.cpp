#include "hitboxes/RectangularHitbox.hpp"

#include "hitboxes/OvalHitbox.hpp"
#include "hitboxes/CircularHitbox.hpp"

#include "utility/functions.hpp"

#include <cmath>
#include <algorithm>
#include <limits>

#include "Constants.hpp"

namespace hitboxes {
RectangularHitbox::RectangularHitbox(const glm::vec2& center, const glm::vec2& dimensions, float rotation)
	: center(center), dimensions(dimensions), rotation(rotation) {
}

bool RectangularHitbox::is_collided_with(std::shared_ptr<I_BaseHitbox> box) const {
	switch (box->get_type()) {
		case HitboxType::CIRCULAR:
			return check_collision_circular(std::static_pointer_cast<CircularHitbox>(box));
		case HitboxType::OVAL:
			return check_collision_oval(std::static_pointer_cast<OvalHitbox>(box));
		case HitboxType::RECTANGULAR:
			return check_collision_rectangular(std::static_pointer_cast<RectangularHitbox>(box));
		default:
			return false; // this should never happen
	}
}

bool RectangularHitbox::check_collision_circular(const std::shared_ptr<CircularHitbox>& circle) const {
	// transform circle to local
	glm::vec2 local_circle_center = transform_to_local_space(circle->get_position());
	
	// find closing point on retangle
	glm::vec2 closest_point_local;
	
	// using clamp to find the closest point on rectangle
	closest_point_local.x = std::clamp(local_circle_center.x, -dimensions.x / 2.0f, dimensions.x / 2.0f);
	closest_point_local.y = std::clamp(local_circle_center.y, -dimensions.y / 2.0f, dimensions.y / 2.0f);
	
	// transform the closest point back to world space
	glm::vec2 closest_point_world = transform_to_world_space(closest_point_local);
	
	// check if distance of closest point is larger than distance if circle center
	float distance = glm::length(closest_point_world - circle->get_position());
	return distance <= circle->get_radius();
}

bool RectangularHitbox::check_collision_oval(const std::shared_ptr<OvalHitbox>& oval) const {
	// rectangle-oval collision is complex
	// this is just an approximation
	
	// check if the rectangle corners are inside oval
	auto corners = get_corners();
	for (const auto& corner : corners) {
		if (oval->contains_point(corner)) {
			return true;
		}
	}
	
	// check if oval center is inside the rectangle
	if (contains_point(oval->get_position())) {
		return true;
	}
	
	// this is approaximation
	// check if sample points on oval is inside the rectangle
	constexpr int NUM_SAMPLES = CONSTANTS::HITBOX_CONSTANTS::RECTANGLE_SAMPLE_COUNT; // number of sample points
	for (int i = 0; i < NUM_SAMPLES; i++) {
		float angle = 2.0f * static_cast<float>(M_PI) * static_cast<float>(i) / NUM_SAMPLES;
		glm::vec2 direction(std::cos(angle), std::sin(angle));
		
		// get direction based on sample number
		// get find the corresponding point
		glm::vec2 rotated_direction = utility::rotate_vec2(direction, oval->get_rotation());
		glm::vec2 point_on_oval = oval->get_position() + glm::vec2(
			rotated_direction.x * oval->get_radii().x,
			rotated_direction.y * oval->get_radii().y
		);
		
		if (contains_point(point_on_oval)) {
			return true;
		}
	}
	
	// check if rectangle edges collides/intersects with oval
	for (size_t i = 0; i < corners.size(); i++) {
		size_t next_i = (i + 1) % corners.size();
		glm::vec2 edge_start = corners[i];
		glm::vec2 edge_end = corners[next_i];
		
		// find the closing point to the edge on the oval
		glm::vec2 edge_vector = edge_end - edge_start;
		float edge_length = glm::length(edge_vector);
		
		if (edge_length < std::numeric_limits<float>::epsilon()) {
			continue; // skips if edge length is close to 0
		}
		
		glm::vec2 oval_to_edge_start = edge_start - oval->get_position();
		
		// calculate the distance between the them using dot
		float t = glm::dot(oval_to_edge_start, edge_vector) / (edge_length*edge_length);
		t = std::clamp(t, 0.0f, 1.0f);
		
		// calculate the closing point on the edge
		glm::vec2 closest_on_edge = edge_start + t * edge_vector;
		
		// checks if this point is inside the oval
		if (oval->contains_point(closest_on_edge)) {
			return true;
		}
	}
	
	return false;
}

bool RectangularHitbox::check_collision_rectangular(const std::shared_ptr<RectangularHitbox>& other) const {
	// using the Separating Axis Theorem (SAT) for rotated rectangles
	
	// get the corners of both rectangles
	auto corners_a = get_corners();
	auto corners_b = other->get_corners();
	
	// we need to check projection onto 4 axes
	// 2 for this rectangle's edges and 2 for the other rectangle's edges
	std::array<glm::vec2, 4> axes;
	
	// axes from this rectangle
	axes[0] = glm::normalize(corners_a[1] - corners_a[0]);
	axes[1] = glm::normalize(corners_a[3] - corners_a[0]);
	
	// axes from the other rectangle
	axes[2] = glm::normalize(corners_b[1] - corners_b[0]);
	axes[3] = glm::normalize(corners_b[3] - corners_b[0]);
	
	// check for separation along each axis
	for (const auto& axis : axes) {
		float min_a = std::numeric_limits<float>::max();
		float max_a = std::numeric_limits<float>::lowest();
		
		// project corners of the first rectangle onto the axis
		for (const auto& corner : corners_a) {
			float projection = glm::dot(corner, axis);
			min_a = std::min(min_a, projection);
			max_a = std::max(max_a, projection);
		}
		
		// project corners of the second rectangle onto the axis
		float min_b = std::numeric_limits<float>::max();
		float max_b = std::numeric_limits<float>::lowest();
		
		for (const auto& corner : corners_b) {
			float projection = glm::dot(corner, axis);
			min_b = std::min(min_b, projection);
			max_b = std::max(max_b, projection);
		}
		
		// if any projections overlaps
		if (max_a < min_b || max_b < min_a) {
			return false;
		}
	}
	
	// no separating axis found, so the rectangles must intersect
	return true;
}

bool RectangularHitbox::contains_point(const glm::vec2& point) const {
	// transform to local points
	glm::vec2 local_point = transform_to_local_space(point);
	
	// checks if point is in dimension
	return (std::abs(local_point.x) <= dimensions.x / 2.0f) &&
		   (std::abs(local_point.y) <= dimensions.y / 2.0f);
}

glm::vec2 RectangularHitbox::get_closest_point(const glm::vec2& point) const {
	// transform to local space
	glm::vec2 local_point = transform_to_local_space(point);
	
	// find closest using clamp
	glm::vec2 closest_local;
	closest_local.x = std::clamp(local_point.x, -dimensions.x / 2.0f, dimensions.x / 2.0f);
	closest_local.y = std::clamp(local_point.y, -dimensions.y / 2.0f, dimensions.y / 2.0f);
	
	// back to world pos
	return transform_to_world_space(closest_local);
}

std::array<glm::vec2, 4> RectangularHitbox::get_corners() const {
	float half_width = dimensions.x / 2.0f;
	float half_height = dimensions.y / 2.0f;
	
	std::array<glm::vec2, 4> local_corners = {
		glm::vec2(-half_width, -half_height),  // bottom left
		glm::vec2(half_width, -half_height),   // bottom right
		glm::vec2(half_width, half_height),	// top right
		glm::vec2(-half_width, half_height)	// top left
	};
	
	// transform each corner to world
	std::array<glm::vec2, 4> world_corners;
	for (size_t i = 0; i < 4; i++) {
		world_corners[i] = transform_to_world_space(local_corners[i]);
	}
	
	return world_corners;
}

glm::vec2 RectangularHitbox::transform_to_local_space(const glm::vec2& point) const {
	// translate point relative to rectangle center
	glm::vec2 centered = point - center;
	
	// rotate
	return utility::rotate_vec2(centered, -rotation);
}

glm::vec2 RectangularHitbox::transform_to_world_space(const glm::vec2& point) const {
	// first rotate
	glm::vec2 rotated = utility::rotate_vec2(point, rotation);
	
	// then transform to world
	return rotated + center;
}

}
