#include "monkeys/TackShooter.hpp"

#include <cmath>

#include "bloons/BaseBloon.hpp"
#include "constants/MONKEY.hpp"
#include "hitboxes/CircularHitbox.hpp"

#include "projectiles/TackProjectile.hpp"
#include "Util/Image.hpp"

#include "utility/functions.hpp"

namespace monkeys {

TackShooter::TackShooter(glm::vec2 position)
: BaseMonkey(position) {
	m_Transform.translation = position;

	auto stat = CONSTANTS::MONKEY::TACK;

	// base monkey initialization
	initialize_with_stat(stat);

	// drawable initialization
	m_Drawable = std::make_shared<Util::Image>(m_image_path, false);
	m_Transform.scale = {stat.IMAGE_SCALE, stat.IMAGE_SCALE};

	// monkey attacker initialization
	m_projectile_spawn_position = {stat.PROJECTILE_SPAWN_X, stat.PROJECTILE_SPAWN_Y};

	m_attack_interval = stat.ATTACK_INTERVAL;
};

void TackShooter::scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) {
	bool bloon_in_radius = utility::hitboxes_are_collided(bloon->get_hitbox(),m_radius_hitbox);

	if (!bloon_in_radius) return;

	if (!can_attack()) return;

	 m_target_bloon = bloon;
};

void TackShooter::reset_target() {
	m_target_bloon = nullptr;
};

std::shared_ptr<bloons::BaseBloon> TackShooter::get_target() {
	return m_target_bloon;
}

std::vector<std::shared_ptr<projectiles::BaseProjectile>> TackShooter::get_spawned_projectile() {
	auto ret = m_spawned_projectile;
	m_spawned_projectile.clear();
	return ret;
}

void TackShooter::update_attack_interval() {
	if (!can_attack()) --m_attack_cooldown;
};

void TackShooter::attack() {
	if (!can_attack()) {
		update_attack_interval();
		return;
	}
	if (m_target_bloon == nullptr) return;

	// uses {0,0} since tack doesn't aim
	spawn_projectile(glm::vec2{0,0});
	m_attack_cooldown = m_attack_interval;
};

bool TackShooter::can_attack() {
	return m_attack_cooldown == 0;
};

void TackShooter::spawn_projectile(glm::vec2 position) {
	auto pos = m_Transform.translation;
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::TackProjectile>(pos, 0.00*M_PI)
	);
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::TackProjectile>(pos, 0.25*M_PI)
	);
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::TackProjectile>(pos, 0.50*M_PI)
	);
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::TackProjectile>(pos, 0.75*M_PI)
	);
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::TackProjectile>(pos, 1.00*M_PI)
	);
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::TackProjectile>(pos, 1.25*M_PI)
	);
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::TackProjectile>(pos, 1.50*M_PI)
	);
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::TackProjectile>(pos, 1.75*M_PI)
	);
}

void TackShooter::face_towards(glm::vec2 position) {
	// TACK SHOOTER DOES NOT ROTATE
}

TackShooter::~TackShooter() {
	
}

}