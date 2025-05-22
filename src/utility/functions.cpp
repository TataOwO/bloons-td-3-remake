#include "utility/functions.hpp"

#include <cmath>

#include "Constants.hpp"
#include "hitboxes/I_BaseHitbox.hpp"

namespace utility {

glm::vec2 rotate_vec2(glm::vec2 vec, float radian) {
	float c = std::cos(radian);
	float s = std::sin(radian);
	
	glm::vec2 ret = {
		c * vec.x - s * vec.y,
		s * vec.x + c * vec.y
	};
	
	return ret;
};

bool hitboxes_are_collided(const std::shared_ptr<hitboxes::I_BaseHitbox> &a, const std::shared_ptr<hitboxes::I_BaseHitbox> &b) {
	int a_type = 0, b_type = 0;
	switch (a->get_type()) {
	case hitboxes::HitboxType::CIRCULAR:
		a_type = CONSTANTS::HITBOX_CONSTANTS::COLLISION_CHECK_PRIORITY::CIRCULAR;
	break;
	case hitboxes::HitboxType::OVAL:
		a_type = CONSTANTS::HITBOX_CONSTANTS::COLLISION_CHECK_PRIORITY::OVAL;
	break;
	case hitboxes::HitboxType::RECTANGULAR:
		a_type = CONSTANTS::HITBOX_CONSTANTS::COLLISION_CHECK_PRIORITY::RECTANGULAR;
	break;
	case hitboxes::HitboxType::GROUP:
		a_type = CONSTANTS::HITBOX_CONSTANTS::COLLISION_CHECK_PRIORITY::GROUP;
	break;
	}
	switch (b->get_type()) {
	case hitboxes::HitboxType::CIRCULAR:
		b_type = CONSTANTS::HITBOX_CONSTANTS::COLLISION_CHECK_PRIORITY::CIRCULAR;
	break;
	case hitboxes::HitboxType::OVAL:
		b_type = CONSTANTS::HITBOX_CONSTANTS::COLLISION_CHECK_PRIORITY::OVAL;
	break;
	case hitboxes::HitboxType::RECTANGULAR:
		b_type = CONSTANTS::HITBOX_CONSTANTS::COLLISION_CHECK_PRIORITY::RECTANGULAR;
	break;
	case hitboxes::HitboxType::GROUP:
		b_type = CONSTANTS::HITBOX_CONSTANTS::COLLISION_CHECK_PRIORITY::GROUP;
	break;
	}
	
	if (a_type > b_type) return a->is_collided_with(b);
	else return b->is_collided_with(a);
}

}
