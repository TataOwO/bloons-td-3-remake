#include "projectiles/DartProjectile.hpp"

#include "Util/Image.hpp"
#include "utility/functions.hpp"

#include <iostream>

namespace projectiles {

DartProjectile::DartProjectile(const glm::vec2& position, float rotation) : BaseProjectile() {
	m_hitbox = std::make_shared<hitboxes::RectangularHitbox>(position, glm::vec2(10,20), rotation);
	
	m_damage = 1;
	m_pierce = 2;
	m_survive_period = 60;
	
	m_Drawable = std::make_shared<Util::Image>(RESOURCE_DIR"/images/dart.png");
	
	m_Transform.scale = {2, 2};
	
	// Setting initial velocity based on rotation
	// Since rotation=0 faces upwards, we need to calculate velocity accordingly
	float speed = 30; // Adjust dart speed as needed
	m_velocity = utility::rotate_vec2(glm::vec2(0, -speed), rotation+3.14);
	
	SetVisible(true);
}

void DartProjectile::update() {
	// Update position based on velocity
	m_move();
	
	// Increment tick counter
	++m_tick;
}

void DartProjectile::deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) {
	// checks if bloon is already hit by this projectile
	for (auto b: m_hit_bloon_vec) {
		if (b == nullptr) continue;
		if (b == bloon) return;
	}
	
	// Reduce pierce when the dart hits a bloon
	if (is_dead()) return;
	
	if (bloon == nullptr) return;
	
	auto bloon_type = bloon->get_type();
	
	int to_be_dealt_damage = m_damage;
	if (bloon_type == bloons::BLOON_TYPE::CERAMIC) to_be_dealt_damage += m_extra_ceramic_damage;
	
	// checks if projectile has the ability to pop this bloon
	if (!m_lead_popping_power && bloon_type == bloons::BLOON_TYPE::LEAD) {
		// play lead sound effect
	}
	else if (!m_white_popping_power && bloon_type == bloons::BLOON_TYPE::WHITE) {
		// handles not popping white
	}
	else if (!m_black_popping_power && bloon_type == bloons::BLOON_TYPE::BLACK) {
		// handles not popping black
	}
	else {
		// if projectile has the abliity to pop this bloon
		bloon->handle_take_damage(m_damage);
	}
	
	// always subtract 1 from pierce, and add bloons to hit vec
	--m_pierce;
	m_hit_bloon_vec.push_back(bloon);
}

void DartProjectile::m_move() {
	glm::vec2 current_position = m_hitbox->get_position();
	
	glm::vec2 new_position = current_position + m_velocity;
	
	m_hitbox->set_position(new_position);
	
	// Update the drawable position to match the hitbox
	m_Transform.translation = new_position;
	
	// Also update rotation of the drawable to match the hitbox
	m_Transform.rotation = m_hitbox->get_rotation();
}

}