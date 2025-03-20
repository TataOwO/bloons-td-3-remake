#include "bloons/Bloon.hpp"

#include <iostream>

namespace bloons {
	Bloon::Bloon(std::shared_ptr<map::route::Route> start_route, bloons::BLOON_TYPE type)
	: BaseBloon(start_route) {
		m_type = type;
		switch(type) {
		case RED    :
			m_hp = 1;
			m_radius = 23;
			m_image_path = RESOURCE_DIR"/images/bloons/red_bloon.png";
			m_speed = 1;
		break;
		case BLUE   :
			m_hp = 2;
			m_radius = 25;
			m_image_path = RESOURCE_DIR"/images/bloons/blue_bloon.png";
			m_speed = 1;
		break;
		case GREEN  :
			m_hp = 3;
			m_radius = 26;
			m_image_path = RESOURCE_DIR"/images/bloons/green_bloon.png";
			m_speed = 1;
		break;
		case YELLOW :
			m_hp = 4;
			m_radius = 27;
			m_image_path = RESOURCE_DIR"/images/bloons/yellow_bloon.png";
			m_speed = 1;
		break;
		case WHITE  :
			m_hp = 6;
			m_radius = 17;
			m_image_path = RESOURCE_DIR"/images/bloons/white_bloon.png";
		break;
		case BLACK  :
			m_hp = 6;
			m_radius = 17;
			m_image_path = RESOURCE_DIR"/images/bloons/black_bloon.png";
			m_speed = 1;
		break;
		case LEAD   :
			m_hp = 6;
			m_radius = 25;
			m_image_path = RESOURCE_DIR"/images/bloons/lead_bloon.png";
			m_speed = 1;
		break;
		case RAINBOW:
			m_hp = 7;
			m_radius = 27;
			m_image_path = RESOURCE_DIR"/images/bloons/rainbow_bloon.png";
			m_speed = 1;
		break;
		case CERAMIC:
			m_hp = 13;
			m_radius = 28;
			m_image_path = RESOURCE_DIR"/images/bloons/ceremic_bloon.png";
			m_speed = 1;
		break;
		case MOAB   :
			m_hp = 200;
			m_radius = 200;
		break;
		default:
		break;
		}
		
		m_speed = 5;
		
		m_Drawable = std::make_shared<Util::Image>(m_image_path);
		
		m_Transform.translation = start_route->get_start_point();
		m_Transform.scale = {1,1};
		
		this->SetZIndex(3);
		this->SetVisible(true);
	};

	void Bloon::update() {
		m_move();
	};
	
	void Bloon::m_take_damage(int damage) {
		std::cout << "damage taken: " << damage << std::endl;
	};
	
}
