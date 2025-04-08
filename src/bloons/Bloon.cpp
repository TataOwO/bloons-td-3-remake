#include "bloons/Bloon.hpp"

#include <iostream>

namespace bloons {
	Bloon::Bloon(std::shared_ptr<map::route::Route> start_route, bloons::BLOON_TYPE type)
	: BaseBloon(start_route) {
		m_type = type;
		
		set_bloon_type(type);
		
		m_Transform.translation = start_route->get_start_point();
		m_Transform.scale = {1,1};
		
		this->SetZIndex(3);
		this->SetVisible(true);
	};

	void Bloon::update() {
		m_move();
	};
	
	void Bloon::TAKE_DAMAGE(int damage) {
		m_take_damage(damage);
		
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
		case 6: 
			set_bloon_type(bloons::BLOON_TYPE::WHITE);
		break;
		case 8: 
			set_bloon_type(bloons::BLOON_TYPE::RAINBOW);
		break;
		default:
		break;
		}
	};
	
	void Bloon::set_bloon_type(bloons::BLOON_TYPE type) {
		switch(type) {
		case RED    :
			m_hp = 1;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 23);
			m_image_path = RESOURCE_DIR"/images/bloons/red_bloon.png";
			m_speed = 3.2;
			m_Drawable = std::make_shared<Util::Image>(m_image_path);
		break;
		case BLUE   :
			m_hp = 2;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 25);
			m_image_path = RESOURCE_DIR"/images/bloons/blue_bloon.png";
			m_speed = 4;
			m_Drawable = std::make_shared<Util::Image>(m_image_path);
		break;
		case GREEN  :
			m_hp = 3;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 26);
			m_image_path = RESOURCE_DIR"/images/bloons/green_bloon.png";
			m_speed = 4.8;
			m_Drawable = std::make_shared<Util::Image>(m_image_path);
		break;
		case YELLOW :
			m_hp = 4;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 27);
			m_image_path = RESOURCE_DIR"/images/bloons/yellow_bloon.png";
			m_speed = 6.4;
			m_Drawable = std::make_shared<Util::Image>(m_image_path);
		break;
		case WHITE  :
			m_hp = 6;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 17);
			m_image_path = RESOURCE_DIR"/images/bloons/white_bloon.png";
			m_speed = 8;
			m_Drawable = std::make_shared<Util::Image>(m_image_path);
		break;
		case BLACK  :
			m_hp = 6;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 17);
			m_image_path = RESOURCE_DIR"/images/bloons/black_bloon.png";
			m_speed = 8;
			m_Drawable = std::make_shared<Util::Image>(m_image_path);
		break;
		case LEAD   :
			m_hp = 6;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 25);
			m_image_path = RESOURCE_DIR"/images/bloons/lead_bloon.png";
			m_speed = 8;
			m_Drawable = std::make_shared<Util::Image>(m_image_path);
		break;
		case RAINBOW:
			m_hp = 7;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 27);
			m_image_path = RESOURCE_DIR"/images/bloons/rainbow_bloon.png";
			m_speed = 10;
			m_Drawable = std::make_shared<Util::Image>(m_image_path);
		break;
		case CERAMIC:
			m_hp = 13;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 28);
			m_image_path = RESOURCE_DIR"/images/bloons/ceramic_bloon.png";
			m_speed = 9.2;
			m_Drawable = std::make_shared<Util::Image>(m_image_path);
		break;
		case MOAB   :
			m_hp = 200;
			m_hitbox = std::make_shared<hitboxes::CircularHitbox>(m_Transform.translation, 200);
		break;
		default:
		break;
		}
	}
	
	void Bloon::m_take_damage(int damage) {
		m_hp -= damage;
	};
}
