#include "bloons/Bloon.hpp"

#include "Constants.hpp"

#include "bloons/BaseBloon.hpp"
#include "hitboxes/CircularHitbox.hpp"
#include "map/route/Route.hpp"
#include "Util/Image.hpp"
#include <string>

namespace bloons {
	Bloon::Bloon(const std::shared_ptr<map::route::Route> &start_route, bloons::BLOON_TYPE type)
	: BaseBloon(start_route) {
		m_type = type;

		set_bloon_type(type);

		m_Transform.translation = start_route->get_start_point();

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
		CONSTANTS::BLOON_CONSTANTS::Bloon stat;
		switch(type) {
		case bloons::BLOON_TYPE::RED    :
			stat = CONSTANTS::BLOON_CONSTANTS::RED;
		break;
		case bloons::BLOON_TYPE::BLUE   :
			stat = CONSTANTS::BLOON_CONSTANTS::BLUE;
		break;
		case bloons::BLOON_TYPE::GREEN  :
			stat = CONSTANTS::BLOON_CONSTANTS::GREEN;
		break;
		case bloons::BLOON_TYPE::YELLOW :
			stat = CONSTANTS::BLOON_CONSTANTS::YELLOW;
		break;
		case bloons::BLOON_TYPE::WHITE  :
			stat = CONSTANTS::BLOON_CONSTANTS::WHITE;
		break;
		case bloons::BLOON_TYPE::BLACK  :
			stat = CONSTANTS::BLOON_CONSTANTS::BLACK;
		break;
		case bloons::BLOON_TYPE::LEAD   :
			stat = CONSTANTS::BLOON_CONSTANTS::LEAD;
		break;
		case bloons::BLOON_TYPE::RAINBOW:
			stat = CONSTANTS::BLOON_CONSTANTS::RAINBOW;
		break;
		case bloons::BLOON_TYPE::CERAMIC:
			stat = CONSTANTS::BLOON_CONSTANTS::CERAMIC;
		break;
		default:
			throw std::invalid_argument("void Bloon::set_bloon_type(bloons::BLOON_TYPE type): UNKNOWN BLOON TYPE");
		break;
		}

		m_type = type;
		m_hp = stat.HP;
		m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, stat.RADIUS);
		m_speed = stat.SPEED;
		m_Drawable = BaseBloon::get_bloon_drawable(type);
	}

	void Bloon::m_take_damage(int damage) {
		// if ceramic, only give 10$ when hp reaches 0
		if (m_type == bloons::BLOON_TYPE::CERAMIC) {
			m_accumulated_money += (m_hp==0)? 10: 0;
		}
		
		m_hp -= damage;
		m_accumulated_money += damage;
	};
}
