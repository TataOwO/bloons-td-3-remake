#include "monkeys/BombShooter.hpp"

#include "Constants.hpp"
#include "bloons/BaseBloon.hpp"
#include "hitboxes/CircularHitbox.hpp"

#include "projectiles/DartProjectile.hpp"
#include "Util/Animation.hpp"

#include "utility/functions.hpp"

namespace monkeys {

BombShooter::BombShooter(glm::vec2 position)
: BaseMonkey(position) {
	m_Transform.translation = position;

	auto stat = CONSTANTS::MONKEY_CONSTANTS::BOMB;

	// base monkey initialization
	initialize_with_stat(stat);

	// drawable initialization
	std::vector<std::string> paths = {};
	for (int i=1; i<=22; ++i) { // 22 frames
		std::string path_name = m_image_path + std::to_string(i) + ".png";
		paths.push_back(path_name);
	}
	m_animation = std::make_shared<Util::Animation>(paths, false, 33, false);
	m_Drawable = m_animation;
	m_Transform.scale = {stat.IMAGE_SCALE, stat.IMAGE_SCALE};

	// monkey attacker initialization
	m_projectile_spawn_position = {stat.PROJECTILE_SPAWN_X, stat.PROJECTILE_SPAWN_Y};

	m_attack_interval = stat.ATTACK_INTERVAL;
};

void BombShooter::scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) {
	bool bloon_in_radius = utility::hitboxes_are_collided(bloon->get_hitbox(),m_radius_hitbox);

	if (!bloon_in_radius) return;

	if (!can_attack()) return;

	 m_target_bloon = bloon;
};

void BombShooter::reset_target() {
	m_target_bloon = nullptr;
};

std::shared_ptr<bloons::BaseBloon> BombShooter::get_target() {
	return m_target_bloon;
}

std::vector<std::shared_ptr<projectiles::BaseProjectile>> BombShooter::get_spawned_projectile() {
	auto ret = m_spawned_projectile;
	m_spawned_projectile.clear();
	return ret;
}

void BombShooter::update_attack_interval() {
	if (!can_attack()) --m_attack_cooldown;
};

void BombShooter::attack() {
	if (!can_attack()) {
		update_attack_interval();
		return;
	}
	if (m_target_bloon == nullptr) return;

	m_animation->Play();
	glm::vec2 bloon_pos = m_target_bloon->get_pos();
	face_towards(bloon_pos);
	spawn_projectile(bloon_pos);
	m_attack_cooldown = m_attack_interval;
};

bool BombShooter::can_attack() {
	return m_attack_cooldown == 0;
};

void BombShooter::spawn_projectile(glm::vec2 position) {
	glm::vec2 projectile_spawn_pos = m_Transform.translation + utility::rotate_vec2(m_projectile_spawn_position, m_Transform.rotation);
	
	glm::vec2 projectile_dir_pos = position - projectile_spawn_pos;
	float projectile_rotation = std::atan2(projectile_dir_pos.y, projectile_dir_pos.x)+0.5*M_PI;
	
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::DartProjectile>(projectile_spawn_pos, projectile_rotation)
	);
}

void BombShooter::face_towards(glm::vec2 position) {
	glm::vec2 m_position = m_base_hitbox->get_position();
	int x_diff = position[0] - m_position[0];
	int y_diff = position[1] - m_position[1];

	m_Transform.rotation = std::atan2(y_diff, x_diff);
};

BombShooter::~BombShooter() {
	
}

}