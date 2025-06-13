#include "projectiles/BombProjectile.hpp"

#include "Util/Image.hpp"
#include "utility/functions.hpp"


#include "bloons/BaseBloon.hpp"
#include "constants/PROJECTILE.hpp"
#include "hitboxes/RectangularHitbox.hpp"

namespace projectiles {

BombProjectile::BombProjectile(const glm::vec2& position, float rotation) : BaseProjectile() {
	m_hitbox = std::make_shared<hitboxes::RectangularHitbox>(position, glm::vec2(10,20), rotation);
	m_Transform.translation = position;
	
	auto stat = CONSTANTS::PROJECTILE::BOMB;
	
	m_damage = stat.DAMAGE;
	m_pierce = stat.PIERCE;
	m_survive_period = stat.SURVIVE_PERIOD;
	
	m_Drawable = std::make_shared<Util::Image>(RESOURCE_DIR"/images/projectiles/bomb/1.png", false);
	
	// m_Transform.scale = {2, 2};
	
	// Setting initial velocity based on rotation
	// Since rotation=0 faces upwards, we need to calculate velocity accordingly
	float speed = stat.SPEED; // Adjust dart speed as needed
	m_velocity = utility::rotate_vec2(glm::vec2(0, -speed), rotation);
	
	SetVisible(true);
}

void BombProjectile::update() {
	// Update position based on velocity
	m_move();
	
	// Increment tick counter
	++m_tick;
}

void BombProjectile::deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) {
	// skips if projectile is dead or bloon doesn't exist
	if (is_dead()) return;
	if (bloon == nullptr) return;
	
	// checks if bloon is already hit by this projectile
	for (const auto& b: m_hit_bloon_vec) {
		if (b == nullptr) continue;
		if (b == bloon) return;
	}
	
	auto bloon_type = bloon->get_type();
	
	int to_be_dealt_damage = m_damage;
	if (bloon_type == CONSTANTS::TYPE::BLOON::CERAMIC) to_be_dealt_damage += m_extra_ceramic_damage;
	
	// checks if projectile has the ability to pop this bloon
	if (!m_lead_popping_power && bloon_type == CONSTANTS::TYPE::BLOON::LEAD) {
		// play lead sound effect
	}
	else if (!m_frozen_popping_power && bloon->is_frozen()) {
		// play ice(lead) sound effect
	}
	else if (!m_white_popping_power && bloon_type == CONSTANTS::TYPE::BLOON::WHITE) {
		// handles not popping white
	}
	else if (!m_black_popping_power && bloon_type == CONSTANTS::TYPE::BLOON::BLACK) {
		// handles not popping black
	}
	else {
		// if projectile has the abliity to pop this bloon
		bloon->handle_take_damage(to_be_dealt_damage);
	}
	
	// always subtract 1 from pierce, and add bloons to hit vec
	--m_pierce;
	m_hit_bloon_vec.push_back(bloon);
}

void BombProjectile::m_move() {
	glm::vec2 current_position = m_hitbox->get_position();
	
	glm::vec2 new_position = current_position + m_velocity;
	
	m_hitbox->set_position(new_position);
	
	// Update the drawable position to match the hitbox
	m_Transform.translation = new_position;
}

BombProjectile::~BombProjectile() {
	
}

}
