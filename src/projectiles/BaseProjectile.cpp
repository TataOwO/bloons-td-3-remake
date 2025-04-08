#include "projectiles/BaseProjectile.hpp"

#include "utility/functions.hpp"

#include "hitboxes/CircularHitbox.hpp"
#include "hitboxes/RectangularHitbox.hpp"

namespace projectiles {

bool BaseProjectile::is_collided_with(std::shared_ptr<bloons::BaseBloon> bloon) {
	std::shared_ptr<hitboxes::I_BaseHitbox> other_hitbox = bloon->get_hitbox();
    return utility::hitboxes_are_collided(m_hitbox, other_hitbox);
}

} // namespace projectiles