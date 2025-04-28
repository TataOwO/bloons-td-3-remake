#include "monkeys/DartMonkey.hpp"

#include "Constants.hpp"
#include "bloons/BaseBloon.hpp"

#include "projectiles/DartProjectile.hpp"

#include "utility/functions.hpp"

namespace monkeys {
	DartMonkey::DartMonkey(glm::vec2 position)
	: BaseMonkey(position) {
		m_image_path = RESOURCE_DIR"/images/dart_monkey_1.5.png";

		m_Transform.translation = position;

		auto stat = CONSTANTS::MONKEY_CONSTANTS::DART;

		m_base_hitbox	->set_radius(stat.BASE_RADIUS);
		m_radius_hitbox	->set_radius(stat.RANGE_RADIUS);

		m_Drawable = std::make_shared<Util::Image>(m_image_path);

		m_projectile_spawn_position = {stat.PROJECTILE_SPAWN_X, stat.PROJECTILE_SPAWN_Y};

		m_attack_interval = stat.ATTACK_INTERVAL;
	};

	void DartMonkey::scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) {
		bool bloon_in_radius = utility::hitboxes_are_collided(bloon->get_hitbox(),m_radius_hitbox);

		if (!bloon_in_radius) return;

		if (!can_attack()) return;

		 m_target_bloon = bloon;
	};

	void DartMonkey::reset_target() {
		m_target_bloon = nullptr;
	};

	std::shared_ptr<bloons::BaseBloon> DartMonkey::get_target() {
		return m_target_bloon;
	}

	std::shared_ptr<projectiles::BaseProjectile> DartMonkey::get_spawned_projectile() {
		std::shared_ptr<projectiles::BaseProjectile> ret = m_spawned_projectile;
		m_spawned_projectile = nullptr;
		return ret;
	}
	
	void DartMonkey::update_attack_interval() {
		if (!can_attack()) --m_attack_cooldown;
	};

	void DartMonkey::attack() {
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

	bool DartMonkey::can_attack() {
		return m_attack_cooldown == 0;
	};

	void DartMonkey::spawn_projectile(glm::vec2 position) {
		glm::vec2 projectile_spawn_pos = m_Transform.translation + utility::rotate_vec2(m_projectile_spawn_position, m_Transform.rotation);
		
		glm::vec2 projectile_dir_pos = position - projectile_spawn_pos;
		float projectile_rotation = std::atan2(projectile_dir_pos.y, projectile_dir_pos.x) - 1.68;
		
		m_spawned_projectile = std::make_shared<projectiles::DartProjectile>(projectile_spawn_pos, projectile_rotation);
	}

	void DartMonkey::face_towards(glm::vec2 position) {
		glm::vec2 m_position = m_base_hitbox->get_position();
		int x_diff = position[0] - m_position[0];
		int y_diff = position[1] - m_position[1];

		m_Transform.rotation = std::atan2(y_diff, x_diff) - 1.68;
	};
}