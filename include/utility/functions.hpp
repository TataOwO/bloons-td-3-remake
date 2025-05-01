#ifndef M_FUNCTIONS_HPP
#define M_FUNCTIONS_HPP

namespace hitboxes {class I_BaseHitbox;}

namespace utility {
	glm::vec2 rotate_vec2(glm::vec2 vec, float radian);
	
	bool hitboxes_are_collided(const std::shared_ptr<hitboxes::I_BaseHitbox> &a, const std::shared_ptr<hitboxes::I_BaseHitbox> &b);
}

#endif
