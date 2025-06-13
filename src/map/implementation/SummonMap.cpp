#include "map/implementation/SummonMap.hpp"

#include <iostream>

#include "CONSTANTS/TYPE.hpp"
#include "handlers/MonkeyManager.hpp"
#include "handlers/PathManager.hpp"
#include "map/MapBackground.hpp"
#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"
#include "hitboxes/CircularHitbox.hpp"
#include "monkeys/BaseMonkey.hpp"
#include "utility/functions.hpp"

namespace map::implementation {

SummonMap::SummonMap(const std::shared_ptr<handlers::MonkeyManager>& monkey_m) : m_monkey_manager(monkey_m) {
	std::vector points = {
		glm::vec2{0, 555},
		glm::vec2{235, 562},
		glm::vec2{252, 534},
		glm::vec2{181, 452},
		glm::vec2{161, 398},
		glm::vec2{167, 281},
		glm::vec2{216, 211},
		glm::vec2{278, 165},
		glm::vec2{355, 146},
		glm::vec2{415, 146},
		glm::vec2{481, 179},
		glm::vec2{538, 228},
		glm::vec2{573, 287},
		glm::vec2{575, 389},
		glm::vec2{558, 451},
		glm::vec2{517, 507},
		glm::vec2{476, 548},
		glm::vec2{486, 573},
		glm::vec2{720, 573},
	};
	
	// routes
	std::vector<std::shared_ptr<map::route::Route>> route_vec1 = {};
	
	glm::vec2 prev = points.at(0);
	for (unsigned int i=1; i<points.size(); ++i) {
		glm::vec2 now = points.at(i);
		route_vec1.push_back(std::make_shared<map::route::Route>(prev, now));
		prev = now;
	}

	// route paths
	std::vector<std::shared_ptr<map::route::RoutePath>> route_paths = {
		std::make_shared<map::route::RoutePath>(route_vec1),
	};

	// add route paths to manager
	m_path_manager = std::make_shared<handlers::PathManager>(route_paths);

	AddChild(m_path_manager);

	// background initialization
	std::vector<std::string> background_images = {
		RESOURCE_DIR"/images/maps/summon_map.png"
	};

	m_background = std::make_shared<map::MapBackground>();
	m_background->set_layers(background_images);
	AddChild(m_background);
	
	// top - dart
	m_dart_placement = std::make_shared<hitboxes::CircularHitbox>(glm::vec2{-120,120}, 36);
	// top right - bomb
	m_bomb_placement = std::make_shared<hitboxes::CircularHitbox>(glm::vec2{-12,48}, 36);
	// bottom right - boomer
	m_boomer_placement = std::make_shared<hitboxes::CircularHitbox>(glm::vec2{-12,-48}, 36);
	// bottom - ice
	m_ice_placement = std::make_shared<hitboxes::CircularHitbox>(glm::vec2{-120,-120}, 36);
	// bottom left - super
	m_super_placement = std::make_shared<hitboxes::CircularHitbox>(glm::vec2{-216,-48}, 36);
	// top left - tack
	m_tack_placement = std::make_shared<hitboxes::CircularHitbox>(glm::vec2{-216,48}, 36);
}

void SummonMap::set_wave(int wave_number) {
	
}

void SummonMap::update() {
	if (m_monkey_manager && !m_god_is_spawned) {
	for (auto& monke: m_monkey_manager->get_all_monkeys()) {
		switch (monke->get_type()) {
		case CONSTANTS::TYPE::MONKEY::DART:
			m_dart_matched |= utility::hitboxes_are_collided(monke->get_hitbox(), m_dart_placement);
		break;
		case CONSTANTS::TYPE::MONKEY::BOMB:
			m_bomb_matched |= utility::hitboxes_are_collided(monke->get_hitbox(), m_bomb_placement);
		break;
		case CONSTANTS::TYPE::MONKEY::BOOMERANG:
			m_boomer_matched |= utility::hitboxes_are_collided(monke->get_hitbox(), m_boomer_placement);
		break;
		case CONSTANTS::TYPE::MONKEY::ICE:
			m_ice_matched |= utility::hitboxes_are_collided(monke->get_hitbox(), m_ice_placement);
		break;
		case CONSTANTS::TYPE::MONKEY::SUPER:
			m_super_matched |= utility::hitboxes_are_collided(monke->get_hitbox(), m_super_placement);
		break;
		case CONSTANTS::TYPE::MONKEY::TACK:
			m_tack_matched |= utility::hitboxes_are_collided(monke->get_hitbox(), m_tack_placement);
		break;
		default: break;
		}
	}
	}
	
	if (!m_god_is_spawned && m_dart_matched && m_bomb_matched && m_boomer_matched && m_ice_matched && m_super_matched && m_tack_matched) {
		std::cout << "monkey god spawned" << std::endl;
		m_monkey_manager->spawn_god_monkey();
		
		m_god_is_spawned = true;
	}
}

SummonMap::~SummonMap() {
}

}

