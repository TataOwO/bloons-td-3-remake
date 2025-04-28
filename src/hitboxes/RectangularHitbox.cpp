#include "hitboxes/RectangularHitbox.hpp"

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
    // Dispatch to the appropriate collision detection method based on the type of the other hitbox
    switch (box->get_type()) {
        case HitboxType::CIRCULAR:
            return check_collision_circular(std::static_pointer_cast<CircularHitbox>(box));
        case HitboxType::OVAL:
            return check_collision_oval(std::static_pointer_cast<OvalHitbox>(box));
        case HitboxType::RECTANGULAR:
            return check_collision_rectangular(std::static_pointer_cast<RectangularHitbox>(box));
        default:
            return false; // Should never happen if all types are handled
    }
}

bool RectangularHitbox::check_collision_circular(const std::shared_ptr<CircularHitbox>& circle) const {
    // Transform the circle's center to rectangle's local space
    glm::vec2 local_circle_center = transform_to_local_space(circle->get_position());
    
    // Find the closest point on the rectangle to the transformed circle center
    glm::vec2 closest_point_local;
    
    // Clamp the circle center to the rectangle bounds to find the closest point
    closest_point_local.x = std::clamp(local_circle_center.x, -dimensions.x / 2.0f, dimensions.x / 2.0f);
    closest_point_local.y = std::clamp(local_circle_center.y, -dimensions.y / 2.0f, dimensions.y / 2.0f);
    
    // Transform the closest point back to world space
    glm::vec2 closest_point_world = transform_to_world_space(closest_point_local);
    
    // Check if the distance from the closest point to the circle center is less than the circle's radius
    float distance = glm::length(closest_point_world - circle->get_position());
    return distance <= circle->get_radius();
}

bool RectangularHitbox::check_collision_oval(const std::shared_ptr<OvalHitbox>& oval) const {
    // Rectangle-oval collision is complex
    // We'll check if any corner of the rectangle is inside the oval
    auto corners = get_corners();
    for (const auto& corner : corners) {
        if (oval->contains_point(corner)) {
            return true;
        }
    }
    
    // Check if the center of the oval is inside the rectangle
    if (contains_point(oval->get_position())) {
        return true;
    }
    
    // Check if any point on the perimeter of the oval intersects with an edge of the rectangle
    // We'll approximate the oval with a number of points
    constexpr int NUM_SAMPLES = CONSTANTS::HITBOX_CONSTANTS::RECTANGLE_SAMPLE_COUNT; // Sample points around the oval
    for (int i = 0; i < NUM_SAMPLES; i++) {
        float angle = 2.0f * static_cast<float>(M_PI) * static_cast<float>(i) / NUM_SAMPLES;
        glm::vec2 direction(std::cos(angle), std::sin(angle));
        
        // Transform direction based on oval's rotation and scale by radii
        glm::vec2 rotated_direction = utility::rotate_vec2(direction, oval->get_rotation());
        glm::vec2 point_on_oval = oval->get_position() + glm::vec2(
            rotated_direction.x * oval->get_radii().x,
            rotated_direction.y * oval->get_radii().y
        );
        
        if (contains_point(point_on_oval)) {
            return true;
        }
    }
    
    // Check rectangle edges against oval
    for (size_t i = 0; i < corners.size(); i++) {
        size_t next_i = (i + 1) % corners.size();
        glm::vec2 edge_start = corners[i];
        glm::vec2 edge_end = corners[next_i];
        
        // Check if this edge intersects with the oval
        // For simplicity, we'll check if the closest point on the line segment to the oval center
        // is within the oval's radius in that direction
        
        glm::vec2 edge_vector = edge_end - edge_start;
        float edge_length = glm::length(edge_vector);
        
        if (edge_length < std::numeric_limits<float>::epsilon()) {
            continue; // Skip degenerate edges
        }
        
        glm::vec2 oval_to_edge_start = edge_start - oval->get_position();
        
        // Calculate how far along the edge the closest point is
        float t = glm::dot(oval_to_edge_start, edge_vector) / (edge_length*edge_length);
        t = std::clamp(t, 0.0f, 1.0f);
        
        // Calculate the closest point on the edge
        glm::vec2 closest_on_edge = edge_start + t * edge_vector;
        
        // Check if this point is inside the oval
        if (oval->contains_point(closest_on_edge)) {
            return true;
        }
    }
    
    return false;
}

bool RectangularHitbox::check_collision_rectangular(const std::shared_ptr<RectangularHitbox>& other) const {
    // Using the Separating Axis Theorem (SAT) for oriented bounding boxes
    
    // Get the corners of both rectangles
    auto corners_a = get_corners();
    auto corners_b = other->get_corners();
    
    // We need to check projection onto 4 axes:
    // 2 for this rectangle's edges and 2 for the other rectangle's edges
    
    // Generate the 4 axes to test
    std::array<glm::vec2, 4> axes;
    
    // Axes from this rectangle's edges
    axes[0] = glm::normalize(corners_a[1] - corners_a[0]);
    axes[1] = glm::normalize(corners_a[3] - corners_a[0]);
    
    // Axes from the other rectangle's edges
    axes[2] = glm::normalize(corners_b[1] - corners_b[0]);
    axes[3] = glm::normalize(corners_b[3] - corners_b[0]);
    
    // Check for separation along each axis
    for (const auto& axis : axes) {
        // Project corners of the first rectangle onto the axis
        float min_a = std::numeric_limits<float>::max();
        float max_a = std::numeric_limits<float>::lowest();
        
        for (const auto& corner : corners_a) {
            float projection = glm::dot(corner, axis);
            min_a = std::min(min_a, projection);
            max_a = std::max(max_a, projection);
        }
        
        // Project corners of the second rectangle onto the axis
        float min_b = std::numeric_limits<float>::max();
        float max_b = std::numeric_limits<float>::lowest();
        
        for (const auto& corner : corners_b) {
            float projection = glm::dot(corner, axis);
            min_b = std::min(min_b, projection);
            max_b = std::max(max_b, projection);
        }
        
        // Check if projections don't overlap
        if (max_a < min_b || max_b < min_a) {
            // Found a separating axis, so the rectangles don't collide
            return false;
        }
    }
    
    // No separating axis found, so the rectangles must intersect
    return true;
}

bool RectangularHitbox::contains_point(const glm::vec2& point) const {
    // Transform point to local space where rectangle is axis-aligned
    glm::vec2 local_point = transform_to_local_space(point);
    
    // In local space, we just need to check if the point is within the dimensions
    return (std::abs(local_point.x) <= dimensions.x / 2.0f) &&
           (std::abs(local_point.y) <= dimensions.y / 2.0f);
}

glm::vec2 RectangularHitbox::get_closest_point(const glm::vec2& point) const {
    // Transform point to local space
    glm::vec2 local_point = transform_to_local_space(point);
    
    // Clamp the point to the rectangle bounds to find the closest point in local space
    glm::vec2 closest_local;
    closest_local.x = std::clamp(local_point.x, -dimensions.x / 2.0f, dimensions.x / 2.0f);
    closest_local.y = std::clamp(local_point.y, -dimensions.y / 2.0f, dimensions.y / 2.0f);
    
    // Transform back to world space
    return transform_to_world_space(closest_local);
}

std::array<glm::vec2, 4> RectangularHitbox::get_corners() const {
    // Half dimensions
    float half_width = dimensions.x / 2.0f;
    float half_height = dimensions.y / 2.0f;
    
    // Calculate the four corners in local space (unrotated)
    std::array<glm::vec2, 4> local_corners = {
        glm::vec2(-half_width, -half_height),  // Bottom-left
        glm::vec2(half_width, -half_height),   // Bottom-right
        glm::vec2(half_width, half_height),    // Top-right
        glm::vec2(-half_width, half_height)    // Top-left
    };
    
    // Transform each corner to world space (apply rotation and translation)
    std::array<glm::vec2, 4> world_corners;
    for (size_t i = 0; i < 4; i++) {
        world_corners[i] = transform_to_world_space(local_corners[i]);
    }
    
    return world_corners;
}

glm::vec2 RectangularHitbox::transform_to_local_space(const glm::vec2& point) const {
    // Translate point relative to rectangle center
    glm::vec2 centered = point - center;
    
    // Rotate point in the opposite direction of the rectangle's rotation
    return utility::rotate_vec2(centered, -rotation);
}

glm::vec2 RectangularHitbox::transform_to_world_space(const glm::vec2& point) const {
    // Rotate the point by the rectangle's rotation
    glm::vec2 rotated = utility::rotate_vec2(point, rotation);
    
    // Translate from local to world coordinates
    return rotated + center;
}

}
