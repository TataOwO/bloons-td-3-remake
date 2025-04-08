#ifndef M_FUNCTIONS_HPP
#define M_FUNCTIONS_HPP

#include "pch.hpp"

#include "hitboxes/I_BaseHitbox.hpp"

namespace utility {
	glm::vec2 rotate_vec2(glm::vec2 vec, float radian);
	
	bool hitboxes_are_collided(std::shared_ptr<hitboxes::I_BaseHitbox> a, std::shared_ptr<hitboxes::I_BaseHitbox> b);
}

#endif
