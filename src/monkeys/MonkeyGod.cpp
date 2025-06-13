#include "monkeys/MonkeyGod.hpp"

#include "bloons/BaseBloon.hpp"
#include "constants/MONKEY.hpp"
#include "hitboxes/CircularHitbox.hpp"

#include "projectiles/GdoProjectile.hpp"
#include "Util/Image.hpp"

#include "utility/functions.hpp"

namespace monkeys {

MonkeyGod::MonkeyGod(glm::vec2 position)
: BaseMonkey(position) {

	m_Transform.translation = position;

	auto stat = CONSTANTS::MONKEY::GOD;

	// base monkey initialization
	initialize_with_stat(stat);

	// drawable initialization
	m_Drawable = std::make_shared<Util::Image>(m_image_path, false);
	m_Transform.scale = {stat.IMAGE_SCALE, stat.IMAGE_SCALE};

	// monkey attacker initialization
	m_projectile_spawn_position = {stat.PROJECTILE_SPAWN_X, stat.PROJECTILE_SPAWN_Y};

	m_attack_interval = stat.ATTACK_INTERVAL;
	
	sold_money = stat.COST * 0.8;
	
	is_attacker = true;
};

void MonkeyGod::scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) {
	// do nothing, as we want to find target in a different way
};

void MonkeyGod::reset_target() {
	m_target_bloon = nullptr;
};

std::shared_ptr<bloons::BaseBloon> MonkeyGod::get_target() {
	return m_target_bloon;
}

std::vector<std::shared_ptr<projectiles::BaseProjectile>> MonkeyGod::get_spawned_projectile() {
	auto ret = m_spawned_projectile;
	m_spawned_projectile.clear();
	return ret;
}

void MonkeyGod::update_attack_interval() {
	if (!can_attack()) --m_attack_cooldown;
};

void MonkeyGod::attack() {
	if (!can_attack()) {
		update_attack_interval();
		return;
	}
	if (m_target_bloon == nullptr) return;

	glm::vec2 bloon_pos = m_target_bloon->get_pos();
	face_towards(bloon_pos);
	spawn_projectile(bloon_pos);
	m_attack_cooldown = m_attack_interval;
};

bool MonkeyGod::can_attack() {
	return m_attack_cooldown == 0;
};

void MonkeyGod::spawn_projectile(glm::vec2 position) {
	glm::vec2 projectile_spawn_pos = m_Transform.translation + utility::rotate_vec2(m_projectile_spawn_position, m_Transform.rotation);
	
	glm::vec2 projectile_dir_pos = position - projectile_spawn_pos;
	float projectile_rotation = std::atan2(projectile_dir_pos.y, projectile_dir_pos.x)+0.5*M_PI;
	
	m_spawned_projectile.push_back(
		std::make_shared<projectiles::GdoProjectile>(projectile_spawn_pos, projectile_rotation)
	);
}

void MonkeyGod::face_towards(glm::vec2 position) {
	glm::vec2 m_position = m_base_hitbox->get_position();
	int x_diff = position[0] - m_position[0];
	int y_diff = position[1] - m_position[1];

	m_Transform.rotation = std::atan2(y_diff, x_diff)+0.5*M_PI;
};


void MonkeyGod::get_random_target(const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec) {
	unsigned int bloon_vec_size = bloon_vec.size();
	
	if (!bloon_vec_size) return;
	
	unsigned int index = std::rand() % bloon_vec_size;
	m_target_bloon = bloon_vec.at(index);
}

MonkeyGod::~MonkeyGod() {
	
}

}