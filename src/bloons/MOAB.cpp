#include "bloons/MOAB.hpp"

#include "bloons/BaseBloon.hpp"
#include "hitboxes/OvalHitbox.hpp"
#include "map/route/Route.hpp"
#include "Util/Image.hpp"
#include <string>
#include <cmath>

#include "constants/BLOON.hpp"

namespace bloons {

MOAB::MOAB(const std::shared_ptr<map::route::Route> &start_route)
: BaseBloon(start_route) {
	m_type = CONSTANTS::TYPE::BLOON::MOAB;
	
	m_hp = CONSTANTS::BLOON::MOAB::HP;
	m_image_path = std::string(CONSTANTS::BLOON::MOAB::IMAGE_PATH);
	m_speed = CONSTANTS::BLOON::MOAB::SPEED;
	auto dim = CONSTANTS::BLOON::MOAB::DIMENSION;
	glm::vec2 dimension = glm::vec2(dim[0], dim[1]);

	m_Transform.translation = start_route->get_start_point();
	
	// sets rotation
	glm::vec2 diff = m_target_point - m_Transform.translation;
	m_Transform.rotation = std::atan2(diff.y, diff.x);

	// hitbox
	m_hitbox = std::make_shared<hitboxes::OvalHitbox>(
		m_Transform.translation,
		dimension,
		m_Transform.rotation
	);
	
	SetDrawable(std::make_shared<Util::Image>(m_image_path + "1.png"));
	m_Transform.scale = {0.5, 0.5};
	this->SetVisible(true);
};

void MOAB::update() {
	// MOAB cannot be frozen
	m_frozen_tick = 0;
	m_move();
	
	// sets rotation
	glm::vec2 diff = m_target_point - m_Transform.translation;
	float target_rotation = std::atan2(diff.y, diff.x);

	// normalize angle
	float angle_diff = target_rotation - m_Transform.rotation;
	while (angle_diff > M_PI) angle_diff -= 2.0f * M_PI;
	while (angle_diff < -M_PI) angle_diff += 2.0f * M_PI;

	// sets the angle
	float next_rotation = m_Transform.rotation + 0.2f * angle_diff;

	m_Transform.rotation = next_rotation;
	m_hitbox->set_rotation(next_rotation);
};

void MOAB::handle_take_damage(int damage) {
	m_take_damage(damage);

	if (m_hp > 150) {
		SetDrawable(std::make_shared<Util::Image>(m_image_path + "1.png"));
	}
	else if (m_hp > 100) {
		SetDrawable(std::make_shared<Util::Image>(m_image_path + "2.png"));
	}
	else if (m_hp > 50) {
		SetDrawable(std::make_shared<Util::Image>(m_image_path + "3.png"));
	}
	else {
		SetDrawable(std::make_shared<Util::Image>(m_image_path + "4.png"));
	}
};

void MOAB::m_take_damage(int damage) {
	m_hp -= damage;
	
	// only gives money when hp reaches 0
	if (m_type == CONSTANTS::TYPE::BLOON::CERAMIC) {
		m_accumulated_money += (m_hp<=0)? 50: 0;
	}
};

MOAB::~MOAB() {
	
}

}
