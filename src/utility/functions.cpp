#include "utility/functions.hpp"

#include <cmath>

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

bool hitboxes_are_collided(std::shared_ptr<hitboxes::I_BaseHitbox> a, std::shared_ptr<hitboxes::I_BaseHitbox> b) {
	int a_type, b_type;
	switch (a->get_type()) {
	case hitboxes::HitboxType::CIRCULAR:
		a_type = 0;
	break;
	case hitboxes::HitboxType::OVAL:
		a_type = 1;
	break;
	case hitboxes::HitboxType::RECTANGULAR:
		a_type = 2;
	break;
	}
	switch (b->get_type()) {
	case hitboxes::HitboxType::CIRCULAR:
		b_type = 0;
	break;
	case hitboxes::HitboxType::OVAL:
		b_type = 1;
	break;
	case hitboxes::HitboxType::RECTANGULAR:
		b_type = 2;
	break;
	}
	
	if (a_type > b_type) return a->is_collided_with(b);
	else return b->is_collided_with(a);
}

}
