#include "projectiles/BaseProjectile.hpp"

#include "bloons/BaseBloon.hpp"
#include "utility/functions.hpp"

namespace projectiles {

bool BaseProjectile::is_collided_with(const std::shared_ptr<bloons::BaseBloon> &bloon) const {
	std::shared_ptr<hitboxes::I_BaseHitbox> other_hitbox = bloon->get_hitbox();
    return utility::hitboxes_are_collided(m_hitbox, other_hitbox);
}

} // namespace projectiles