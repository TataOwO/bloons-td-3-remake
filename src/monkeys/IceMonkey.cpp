#include "monkeys/IceMonkey.hpp"

#include "Constants.hpp"
#include "bloons/BaseBloon.hpp"
#include "hitboxes/CircularHitbox.hpp"

#include "projectiles/DartProjectile.hpp"
#include "Util/Animation.hpp"

#include "utility/functions.hpp"

namespace monkeys {
	IceMonkey::IceMonkey(glm::vec2 position)
	: BaseMonkey(position) {
		m_Transform.translation = position;

		auto stat = CONSTANTS::MONKEY_CONSTANTS::ICE;

		// base monkey initialization
		initialize_with_stat(stat);

		// drawable initialization
		std::vector<std::string> paths = {m_image_path};
		auto animation = std::make_shared<Util::Animation>(paths, true, 0.03f);
		m_Drawable = animation;
		m_Transform.scale = {1.5, 1.5};

		// monkey attacker initialization
		m_projectile_spawn_position = {stat.PROJECTILE_SPAWN_X, stat.PROJECTILE_SPAWN_Y};

		m_attack_interval = stat.ATTACK_INTERVAL;
	};

	void IceMonkey::scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) {
		bool bloon_in_radius = utility::hitboxes_are_collided(bloon->get_hitbox(),m_radius_hitbox);

		if (!bloon_in_radius) return;

		if (!can_attack()) return;

		 m_target_bloon = bloon;
	};

	void IceMonkey::reset_target() {
		m_target_bloon = nullptr;
	};

	std::shared_ptr<bloons::BaseBloon> IceMonkey::get_target() {
		return m_target_bloon;
	}

	std::vector<std::shared_ptr<projectiles::BaseProjectile>> IceMonkey::get_spawned_projectile() {
		auto ret = m_spawned_projectile;
		m_spawned_projectile.clear();
		return ret;
	}
	
	void IceMonkey::update_attack_interval() {
		if (!can_attack()) --m_attack_cooldown;
	};

	void IceMonkey::attack() {
		if (!can_attack()) {
			update_attack_interval();
			return;
		}
		if (m_target_bloon == nullptr) return;

		// uses {0,0} as ice monkey doesn't rotate
		spawn_projectile(glm::vec2{0,0});
		m_attack_cooldown = m_attack_interval;
	};

	bool IceMonkey::can_attack() {
		return m_attack_cooldown == 0;
	};

	void IceMonkey::spawn_projectile(glm::vec2 position) {
		// TODO: USES ICE PROJECTILE
		m_spawned_projectile.push_back(
			std::make_shared<projectiles::DartProjectile>(m_Transform.translation, 0.0f)
		);
	}

	void IceMonkey::face_towards(glm::vec2 position) {
		// NO IMPLEMENTATION
		// ice monkey does not rotate
	};
}