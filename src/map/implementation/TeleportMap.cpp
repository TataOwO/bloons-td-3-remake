#include "map/implementation/TeleportMap.hpp"

#include "handlers/PathManager.hpp"
#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"
#include "Util/Animation.hpp"

#include <iostream>

#include "map/MapBackground.hpp"

namespace map::implementation {

TeleportMap::TeleportMap() {
	// routes
	std::vector<std::shared_ptr<map::route::Route>> state1_route_vec1 = {
		std::make_shared<map::route::Route>(glm::vec2{68,0}, glm::vec2{219,478}),
		std::make_shared<map::route::Route>(glm::vec2{325,203}, glm::vec2{720,76}, true)
	};
	std::vector<std::shared_ptr<map::route::Route>> state1_route_vec2 = {
		std::make_shared<map::route::Route>(glm::vec2{636,720}, glm::vec2{494,267}),
		std::make_shared<map::route::Route>(glm::vec2{383,532}, glm::vec2{0,659}, true)
	};

	std::vector<std::shared_ptr<map::route::Route>> state2_route_vec1 = {
		std::make_shared<map::route::Route>(glm::vec2{636,720}, glm::vec2{481,264}),
		std::make_shared<map::route::Route>(glm::vec2{325,203}, glm::vec2{720,76}, true)
	};
	std::vector<std::shared_ptr<map::route::Route>> state2_route_vec2 = {
		std::make_shared<map::route::Route>(glm::vec2{68,0}, glm::vec2{233,479}),
		std::make_shared<map::route::Route>(glm::vec2{383,532}, glm::vec2{0,659}, true)
	};

	std::vector<std::shared_ptr<map::route::RoutePath>> rps1 = {
		std::make_shared<map::route::RoutePath>(state1_route_vec1),
		std::make_shared<map::route::RoutePath>(state1_route_vec2),
	};

	std::vector<std::shared_ptr<map::route::RoutePath>> rps2 = {
		std::make_shared<map::route::RoutePath>(state2_route_vec1),
		std::make_shared<map::route::RoutePath>(state2_route_vec2),
	};

	m_wave_paths = {
		std::make_shared<handlers::PathManager>(rps2),
		std::make_shared<handlers::PathManager>(rps1),
	};

	m_path_manager = m_wave_paths.at(0);

	// getting animation vectors
	std::vector<std::string> anim1 = {
		RESOURCE_DIR"/images/maps/teleport_map_1.png",
		RESOURCE_DIR"/images/maps/teleport_map_2.png",
		RESOURCE_DIR"/images/maps/teleport_map_3.png",
		RESOURCE_DIR"/images/maps/teleport_map_3.png",
		RESOURCE_DIR"/images/maps/teleport_map_3.png",
		RESOURCE_DIR"/images/maps/teleport_map_4.png",
		RESOURCE_DIR"/images/maps/teleport_map_5.png",
	};
	std::vector<std::string> anim2 = {
		RESOURCE_DIR"/images/maps/teleport_map_5.png",
		RESOURCE_DIR"/images/maps/teleport_map_6.png",
		RESOURCE_DIR"/images/maps/teleport_map_7.png",
		RESOURCE_DIR"/images/maps/teleport_map_7.png",
		RESOURCE_DIR"/images/maps/teleport_map_7.png",
		RESOURCE_DIR"/images/maps/teleport_map_8.png",
		RESOURCE_DIR"/images/maps/teleport_map_1.png",
	};

	m_animations_vec = {
		std::make_shared<Util::Animation>(anim1,false,42,false),
		std::make_shared<Util::Animation>(anim2,false,42,false),
	};
	
	m_animation = m_animations_vec.at(1);
	SetDrawable(m_animation);
	m_Transform.translation = {-120,0};
	
	// background initialization
	std::vector<std::string> background_images = {
		RESOURCE_DIR"/images/maps/teleport_map_background.png",
	};
	
	m_background = std::make_shared<map::MapBackground>();
	m_background->set_layers(background_images);
	AddChild(m_background);
}

void TeleportMap::set_wave(int wave_number) {
	if (wave_number == m_current_wave) return;
	m_current_wave = wave_number;

	RemoveChild(m_path_manager);
	m_path_manager = m_wave_paths.at(m_current_wave%2);
	AddChild(m_path_manager);
	m_animation->Play();
	SetDrawable(m_animation);
	m_animation_was_playing = true;

	std::cout << "current wave: " << m_current_wave << std::endl;
}

void TeleportMap::update() {
	// if the previous animation ended
	if (m_animation_was_playing && m_animation->GetState() != Util::Animation::State::PLAY) {
		// update to the new animation
		m_animation = m_animations_vec.at(m_current_wave%2);
		SetDrawable(m_animation);
		m_animation_was_playing = false;
	}
}

}
