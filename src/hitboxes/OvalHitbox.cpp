#include "hitboxes/OvalHitbox.hpp"

#include "hitboxes/CircularHitbox.hpp"
#include "hitboxes/RectangularHitbox.hpp"

#include "utility/functions.hpp"

#include <cmath>
#include <algorithm>
#include <exception>

namespace hitboxes {

OvalHitbox::OvalHitbox(const glm::vec2& center, const glm::vec2& radii, float rotation)
    : center(center), radii(radii), rotation(rotation) {
}

bool OvalHitbox::is_collided_with(std::shared_ptr<I_BaseHitbox> box) const {
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

bool OvalHitbox::check_collision_circular(const std::shared_ptr<CircularHitbox>& other) const {
	// convert to local pos
    glm::vec2 local_circle_center = transform_to_local_space(other->get_position());
    
    glm::vec2 closest_on_unit_circle;
    if (glm::length(local_circle_center) < std::numeric_limits<float>::epsilon()) {
        // If the circle center is at our local origin, pick an arbitrary point on the unit circle
        closest_on_unit_circle = glm::vec2(1.0f, 0.0f);
    } else {
        // Otherwise normalize to get closest point on unit circle
        closest_on_unit_circle = glm::normalize(local_circle_center);
    }
    
    // Scale by the oval's radii to get the closest point on the oval
    glm::vec2 closest_on_oval = glm::vec2(
        closest_on_unit_circle.x * radii.x,
        closest_on_unit_circle.y * radii.y
    );
    
    // Transform back to world space
    glm::vec2 closest_world = transform_to_world_space(closest_on_oval);
    
    // Check if distance from the closest point to the circle center is less than the circle's radius
    float distance = glm::length(closest_world - other->get_position());
    return distance <= other->get_radius();
}

bool OvalHitbox::check_collision_oval(const std::shared_ptr<OvalHitbox>& other) const {
    // Oval-oval collision is complex. We'll use a conservative approximation based on sampling points
    const int NUM_SAMPLES = 8; // Sample points around each oval
    
    // Sample points around this oval and check if any are inside the other oval
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
    
    // Sample points around the other oval and check if any are inside this oval
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
	return 0;
}

bool OvalHitbox::contains_point(const glm::vec2& point) const {
    // Transform point to local space
    glm::vec2 local_point = transform_to_local_space(point);
    
    // In local space, we can use the standard formula for point-in-ellipse:
    // (x/a)² + (y/b)² <= 1
    float normalized_x = local_point.x / radii.x;
    float normalized_y = local_point.y / radii.y;
    
    return (normalized_x * normalized_x + normalized_y * normalized_y) <= 1.0f;
}

glm::vec2 OvalHitbox::get_closest_point(const glm::vec2& point) const {
    // Transform the point to local space
    glm::vec2 local_point = transform_to_local_space(point);
    
    // Handle the case where the point is at the origin
    if (glm::length(local_point) < std::numeric_limits<float>::epsilon()) {
        // Return a point on the right edge of the oval
        return transform_to_world_space(glm::vec2(radii.x, 0.0f));
    }
    
    // Algorithm to find the closest point on an ellipse to a point:
    // This is an iterative approximation as there's no closed-form solution
    
    // Start with a normalized direction to the point
    glm::vec2 direction = glm::normalize(local_point);
    
    // Scale by radii to get a point on the ellipse in this direction
    glm::vec2 closest_on_oval = glm::vec2(
        direction.x * radii.x,
        direction.y * radii.y
    );
    
    // Transform back to world space
    return transform_to_world_space(closest_on_oval);
}

glm::vec2 OvalHitbox::transform_to_local_space(const glm::vec2& point) const {
    // Translate point relative to oval center
    glm::vec2 centered = point - center;
    
    // Rotate point in the opposite direction of the oval's rotation
    return utility::rotate_vec2(centered, -rotation);
}

glm::vec2 OvalHitbox::transform_to_world_space(const glm::vec2& point) const {
    // Rotate the point by the oval's rotation
    glm::vec2 rotated = utility::rotate_vec2(point, rotation);
    
    // Translate from local to world coordinates
    return rotated + center;
}

}
