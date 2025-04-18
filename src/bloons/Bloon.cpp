#include "bloons/Bloon.hpp"

#include <iostream>
#include <cstdlib>

#include <exception>

#include "Constants.hpp"

namespace bloons {
	Bloon::Bloon(std::shared_ptr<map::route::Route> start_route, bloons::BLOON_TYPE type)
	: BaseBloon(start_route) {
		m_type = type;

		set_bloon_type(type);

		m_Transform.translation = start_route->get_start_point();

		// random between 3~4
		this->SetZIndex(3 + (std::rand()%100)*0.01);
		this->SetVisible(true);
	};

	void Bloon::update() {
		m_move();
	};

	void Bloon::handle_take_damage(int damage) {
		m_take_damage(damage);

		// don't change type when the target bloon is ceramic, rainbow, or moab
		switch (m_type) {
		case bloons::BLOON_TYPE::RAINBOW:
		case bloons::BLOON_TYPE::CERAMIC:
		case bloons::BLOON_TYPE::MOAB:
			return;
		default: break;
		}

		switch (m_hp) {
		case 1:
			set_bloon_type(bloons::BLOON_TYPE::RED);
		break;
		case 2:
			set_bloon_type(bloons::BLOON_TYPE::BLUE);
		break;
		case 3:
			set_bloon_type(bloons::BLOON_TYPE::GREEN);
		break;
		case 4:
			set_bloon_type(bloons::BLOON_TYPE::YELLOW);
		break;
		default:
		break;
		}
	};

	void Bloon::set_bloon_type(bloons::BLOON_TYPE type) {
		CONSTANTS::Bloon stat;
		switch(type) {
		case bloons::BLOON_TYPE::RED    :
			stat = CONSTANTS::BloonConstants::RED;
		break;
		case bloons::BLOON_TYPE::BLUE   :
			stat = CONSTANTS::BloonConstants::BLUE;
		break;
		case bloons::BLOON_TYPE::GREEN  :
			stat = CONSTANTS::BloonConstants::GREEN;
		break;
		case bloons::BLOON_TYPE::YELLOW :
			stat = CONSTANTS::BloonConstants::YELLOW;
		break;
		case bloons::BLOON_TYPE::WHITE  :
			stat = CONSTANTS::BloonConstants::WHITE;
		break;
		case bloons::BLOON_TYPE::BLACK  :
			stat = CONSTANTS::BloonConstants::BLACK;
		break;
		case bloons::BLOON_TYPE::LEAD   :
			stat = CONSTANTS::BloonConstants::LEAD;
		break;
		case bloons::BLOON_TYPE::RAINBOW:
			stat = CONSTANTS::BloonConstants::RAINBOW;
		break;
		case bloons::BLOON_TYPE::CERAMIC:
			stat = CONSTANTS::BloonConstants::CERAMIC;
		break;
		default:
			throw std::invalid_argument("void Bloon::set_bloon_type(bloons::BLOON_TYPE type): UNKNOWN BLOON TYPE");
		break;
		}

		m_type = type;
		m_hp = stat.hp;
		m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, stat.radius);
		m_image_path = stat.image_path;
		m_speed = stat.speed;
		m_Drawable = std::make_shared<Util::Image>(m_image_path);
	}

	void Bloon::m_take_damage(int damage) {
		m_hp -= damage;
		m_accumulated_money += damage;
	};
}
