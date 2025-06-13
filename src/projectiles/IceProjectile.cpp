#include "projectiles/IceProjectile.hpp"

#include "Util/Image.hpp"
#include "utility/functions.hpp"


#include "bloons/BaseBloon.hpp"
#include "constants/PROJECTILE.hpp"
#include "hitboxes/CircularHitbox.hpp"

namespace projectiles {

IceProjectile::IceProjectile(const glm::vec2& position, float rotation) : BaseProjectile() {
	m_hitbox = std::make_shared<hitboxes::CircularHitbox>(position, 60);
	m_Transform.translation = position;

	auto stat = CONSTANTS::PROJECTILE::ICE;

	m_damage = stat.DAMAGE;
	m_pierce = stat.PIERCE;
	m_survive_period = stat.SURVIVE_PERIOD;

	SetVisible(false);

	// Setting initial velocity based on rotation
	// Since rotation=0 faces upwards, we need to calculate velocity accordingly
	float speed = stat.SPEED; // Adjust dart speed as needed
	m_velocity = utility::rotate_vec2(glm::vec2(0, -speed), rotation);

	SetVisible(true);
	
	m_lead_popping_power = true;
	m_frozen_popping_power = true;
	m_white_popping_power = false;
}

void IceProjectile::update() {
	// Update position based on velocity
	m_move();

	// Increment tick counter
	++m_tick;
}

void IceProjectile::deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) {
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
		bloon->set_frozen(36);
	}

	// always subtract 1 from pierce, and add bloons to hit vec
	--m_pierce;
	m_hit_bloon_vec.push_back(bloon);
}

void IceProjectile::m_move() {
	glm::vec2 current_position = m_hitbox->get_position();

	glm::vec2 new_position = current_position + m_velocity;

	m_hitbox->set_position(new_position);

	// Update the drawable position to match the hitbox
	m_Transform.translation = new_position;

	// Also update rotation of the drawable to match the hitbox
	m_Transform.rotation = m_hitbox->get_rotation();
}

IceProjectile::~IceProjectile() {

}

}
