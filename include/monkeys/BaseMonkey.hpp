#ifndef BASE_MONKEY_HPP
#define BASE_MONKEY_HPP

#include <string>

#include "Util/GameObject.hpp"

#include "hitboxes/I_BaseHitbox.hpp"
#include "hitboxes/CircularHitbox.hpp"

#include "map/route/Route.hpp"

#include "bloons/BaseBloon.hpp"

#include "projectiles/BaseProjectile.hpp"

namespace monkeys {

class BaseMonkey : public Util::GameObject {
protected:
	BaseMonkey(glm::vec2 position);

public:
	BaseMonkey(const BaseMonkey&) = delete;

	BaseMonkey(BaseMonkey&&) = delete;

	BaseMonkey& operator=(const BaseMonkey&) = delete;

	BaseMonkey& operator=(BaseMonkey&&) = delete;

	virtual ~BaseMonkey() override = default;

	bool is_collided_with_route(const std::shared_ptr<map::route::Route> &route) const;

	bool is_collided_with_monkey(const std::shared_ptr<BaseMonkey> &monke) const;

	float get_radius() const;

	glm::vec2 get_position() const;

	std::shared_ptr<hitboxes::CircularHitbox> get_hitbox() {return m_base_hitbox;}
protected:

protected:
	std::string m_image_path;

	// for route collision
	std::shared_ptr<hitboxes::CircularHitbox> m_base_hitbox;

	// for buff/attack radius
	std::shared_ptr<hitboxes::CircularHitbox> m_radius_hitbox;

	// for bloons
	glm::vec2 m_face_position;
};

class I_MonkeyAttacker {
public:
	virtual void attack() = 0;

	virtual bool can_attack() = 0;

	virtual void scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) = 0;

	virtual void reset_target() = 0;

	virtual std::shared_ptr<bloons::BaseBloon> get_target() = 0;

	virtual bool has_projectile() = 0;

	virtual std::shared_ptr<projectiles::BaseProjectile> get_spawned_projectile() = 0;
protected:
	virtual void update_attack_interval() = 0;

	virtual void face_towards(glm::vec2 position) = 0;

	virtual void spawn_projectile(glm::vec2 position) = 0;
protected:
	glm::vec2 m_projectile_spawn_position = {};

	int m_attack_interval = 0;
	int m_attack_cooldown = 0;

	std::shared_ptr<projectiles::BaseProjectile> m_spawned_projectile;

	std::shared_ptr<bloons::BaseBloon> m_target_bloon = nullptr;
};

}

#endif