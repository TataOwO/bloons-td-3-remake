#ifndef BASE_PROJECTILE_HPP
#define BASE_PROJECTILE_HPP

#include "pch.hpp"

#include "Util/GameObject.hpp"
#include "hitboxes/I_BaseHitbox.hpp"
#include "bloons/BaseBloon.hpp"

namespace projectiles {

class BaseProjectile : public Util::GameObject {
protected:
	BaseProjectile() = default;

public:
	// Disable copying and moving
	BaseProjectile(const BaseProjectile&) = delete;
	BaseProjectile(BaseProjectile&&) = delete;
	BaseProjectile& operator=(const BaseProjectile&) = delete;
	BaseProjectile& operator=(BaseProjectile&&) = delete;

	virtual ~BaseProjectile() = default;

	// Check collision with another hitbox
	bool is_collided_with(std::shared_ptr<bloons::BaseBloon> bloon);

	// Update the projectile's state (e.g., movement)
	virtual void update() = 0;

	bool is_dead() {return m_pierce==0 || m_tick>=m_survive_period;}

	std::shared_ptr<hitboxes::I_BaseHitbox> get_hitbox() { return m_hitbox; }
	
	virtual void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) = 0;

protected:
	std::shared_ptr<hitboxes::I_BaseHitbox> m_hitbox;

	int m_damage = 0;

	// how long the projectile should last
	int m_tick = 0;
	int m_survive_period = 0;
	
	// how many bloons can a projectile hit
	int m_pierce = 0;
	
	// x and y velocity
    glm::vec2 m_velocity = {0,0};

	std::vector<std::shared_ptr<bloons::BaseBloon>> m_hit_bloon_vec;
protected:
	virtual void m_move() = 0;
};

}

#endif