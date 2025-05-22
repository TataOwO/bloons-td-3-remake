#include "hitboxes/HitboxGroup.hpp"

#include "utility/functions.hpp"

namespace hitboxes {

bool HitboxGroup::is_collided_with(std::shared_ptr<I_BaseHitbox> box) const {
	for (auto& hitbox: m_hitboxes) {
		if (utility::hitboxes_are_collided(hitbox, box)) return true;
	}
	return false;
}

bool HitboxGroup::contains_point(const glm::vec2& point) const {
	for (auto& hitbox: m_hitboxes) {
		if (hitbox->contains_point(point)) return true;
	}
	return false;
}

void HitboxGroup::add_hitboxes(const std::vector<std::shared_ptr<I_BaseHitbox>>& hitboxes) {
	m_hitboxes.insert(m_hitboxes.end(), hitboxes.begin(), hitboxes.end());
}

}
