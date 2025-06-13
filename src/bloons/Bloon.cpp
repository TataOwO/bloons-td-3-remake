#include "bloons/Bloon.hpp"


#include "bloons/BaseBloon.hpp"
#include "hitboxes/CircularHitbox.hpp"
#include "map/route/Route.hpp"
#include "Util/Image.hpp"
#include <string>

#include "constants/BLOON.hpp"

namespace bloons {

Bloon::Bloon(const std::shared_ptr<map::route::Route> &start_route, CONSTANTS::TYPE::BLOON type)
: BaseBloon(start_route) {
	m_type = type;

	set_bloon_type(type);

	m_Transform.translation = start_route->get_start_point();

	this->SetVisible(true);
};

void Bloon::update() {
	m_move();
};

int Bloon::get_damage() const {
	if (m_type == CONSTANTS::TYPE::BLOON::CERAMIC) return 60;
	if (m_type == CONSTANTS::TYPE::BLOON::RAINBOW) return 20;
	return get_hp();
}

void Bloon::handle_take_damage(int damage) {
	m_take_damage(damage);

	// don't change type when the target bloon is rainbow or moab
	switch (m_type) {
	case CONSTANTS::TYPE::BLOON::RAINBOW:
	case CONSTANTS::TYPE::BLOON::MOAB:
		return;
	// if it is ceramic, simply changes the image
	case CONSTANTS::TYPE::BLOON::CERAMIC: {
		int image_id = 11-m_hp; // images from 1~10
		if (image_id>10) image_id = 10;
		std::string prefix = RESOURCE_DIR"/images/bloons/ceremic/";
		std::string image_path = prefix + std::to_string(image_id) + ".png";
		m_Drawable = std::make_shared<Util::Image>(std::string(image_path));
	}
	return;
	default: break;
	}

	switch (m_hp) {
	case 1:
		set_bloon_type(CONSTANTS::TYPE::BLOON::RED);
	break;
	case 2:
		set_bloon_type(CONSTANTS::TYPE::BLOON::BLUE);
	break;
	case 3:
		set_bloon_type(CONSTANTS::TYPE::BLOON::GREEN);
	break;
	case 4:
		set_bloon_type(CONSTANTS::TYPE::BLOON::YELLOW);
	break;
	default:
	break;
	}
};

void Bloon::set_bloon_type(CONSTANTS::TYPE::BLOON type) {
	CONSTANTS::BLOON::Bloon stat;
	switch(type) {
	case CONSTANTS::TYPE::BLOON::RED    :
		stat = CONSTANTS::BLOON::RED;
	break;
	case CONSTANTS::TYPE::BLOON::BLUE   :
		stat = CONSTANTS::BLOON::BLUE;
	break;
	case CONSTANTS::TYPE::BLOON::GREEN  :
		stat = CONSTANTS::BLOON::GREEN;
	break;
	case CONSTANTS::TYPE::BLOON::YELLOW :
		stat = CONSTANTS::BLOON::YELLOW;
	break;
	case CONSTANTS::TYPE::BLOON::WHITE  :
		stat = CONSTANTS::BLOON::WHITE;
	break;
	case CONSTANTS::TYPE::BLOON::BLACK  :
		stat = CONSTANTS::BLOON::BLACK;
	break;
	case CONSTANTS::TYPE::BLOON::LEAD   :
		stat = CONSTANTS::BLOON::LEAD;
	break;
	case CONSTANTS::TYPE::BLOON::RAINBOW:
		stat = CONSTANTS::BLOON::RAINBOW;
	break;
	case CONSTANTS::TYPE::BLOON::CERAMIC:
		stat = CONSTANTS::BLOON::CERAMIC;
	break;
	default:
		throw std::invalid_argument("void Bloon::set_bloon_type(CONSTANTS::TYPE::BLOON type): UNKNOWN BLOON TYPE");
	break;
	}

	m_type = type;
	m_hp = stat.HP;
	m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, stat.RADIUS);
	m_speed = stat.SPEED;
	m_Drawable = BaseBloon::get_bloon_drawable(type);
}

void Bloon::m_take_damage(int damage) {
	m_hp -= damage;
	
	// if ceramic, only give 10$ when hp reaches 0
	if (m_type == CONSTANTS::TYPE::BLOON::CERAMIC) {
		m_accumulated_money += (m_hp==0)? 10: 0;
	} else {
		m_accumulated_money += damage;
	}
};

Bloon::~Bloon() {
	
}

}
