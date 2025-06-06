#include "logics/MapSelector.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

#include "hitboxes/RectangularHitbox.hpp"

#include "map/MapBackground.hpp"
	
#include "layout/Button.hpp"
#include "map/implementation/BaseMap.hpp"

namespace logics {

MapSelector::MapSelector() {
	m_peaceful_background = std::make_shared<map::MapBackground>();
	m_peaceful_background->set_layers(std::vector<std::string>{RESOURCE_DIR"/images/maps/peaceful_map.png"});
	m_ice_background = std::make_shared<map::MapBackground>();
	m_ice_background->set_layers(std::vector<std::string>{RESOURCE_DIR"/images/maps/ice_map.png",RESOURCE_DIR"/images/maps/ice_map_frozen.png",RESOURCE_DIR"/images/maps/ice_map_sleeping_frog.png"});
	m_teleport_background = std::make_shared<map::MapBackground>();
	m_teleport_background->set_layers(std::vector<std::string>{RESOURCE_DIR"/images/maps/teleport_map_background.png", RESOURCE_DIR"/images/maps/teleport_map_1.png"});
	m_summon_background = std::make_shared<map::MapBackground>();
	m_summon_background->set_layers(std::vector<std::string>{RESOURCE_DIR"/images/maps/summon_map.png"});
	
	m_background = std::make_shared<map::MapBackground>();
	m_background = m_peaceful_background;
	AddChild(m_background);
	
	auto dark_background = std::make_shared<Util::GameObject>();
	dark_background->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/dark_background.png"));
	AddChild(dark_background);
	dark_background->SetZIndex(1);
	
	peaceful_button = std::make_shared<layout::Button>();
	auto peaceful_hitbox = std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{-288,0}, glm::vec2{180,180}, 0);
	peaceful_button->set_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/maps/peaceful_map.png"));
	peaceful_button->set_hover_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/maps/peaceful_map_yellow.png"));
	peaceful_button->set_on_click([&]() {
		m_spawn_map_type = CONSTANTS::TYPE::MAP::PEACEFUL;
		has_map = true;
		return true;
	});
	peaceful_button->set_removal([](){return false;});
	peaceful_button->set_hitbox(peaceful_hitbox);
	peaceful_button->SetZIndex(2);
	peaceful_button->m_Transform.translation = peaceful_hitbox->get_position();
	AddChild(peaceful_button);
	m_button_vec.push_back(peaceful_button);
	
	ice_button = std::make_shared<layout::Button>();
	auto ice_hitbox = std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{-96,0}, glm::vec2{180,180}, 0);
	ice_button->set_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/maps/ice_map.png"));
	ice_button->set_hover_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/maps/ice_map_yellow.png"));
	ice_button->set_on_click([&]() {
		m_spawn_map_type = CONSTANTS::TYPE::MAP::ICE;
		has_map = true;
		return true;
	});
	ice_button->set_removal([](){return false;});
	ice_button->set_hitbox(ice_hitbox);
	ice_button->SetZIndex(2);
	ice_button->m_Transform.translation = ice_hitbox->get_position();
	AddChild(ice_button);
	m_button_vec.push_back(ice_button);
	
	summon_button = std::make_shared<layout::Button>();
	auto summon_hitbox = std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{96,0}, glm::vec2{180,180}, 0);
	summon_button->set_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/maps/summon_map.png"));
	summon_button->set_hover_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/maps/summon_map_yellow.png"));
	summon_button->set_on_click([&]() {
		m_spawn_map_type = CONSTANTS::TYPE::MAP::SUMMON;
		has_map = true;
		return true;
	});
	summon_button->set_removal([](){return false;});
	summon_button->set_hitbox(summon_hitbox);
	summon_button->SetZIndex(2);
	summon_button->m_Transform.translation = summon_hitbox->get_position();
	AddChild(summon_button);
	m_button_vec.push_back(summon_button);
	
	teleport_button = std::make_shared<layout::Button>();
	auto teleport_hitbox = std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{288,0}, glm::vec2{180,180}, 0);
	teleport_button->set_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/maps/teleport_map.png"));
	teleport_button->set_hover_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/maps/teleport_map_yellow.png"));
	teleport_button->set_on_click([&]() {
		m_spawn_map_type = CONSTANTS::TYPE::MAP::TELEPORT;
		has_map = true;
		return true;
	});
	teleport_button->set_removal([](){return false;});
	teleport_button->set_hitbox(teleport_hitbox);
	teleport_button->SetZIndex(2);
	teleport_button->m_Transform.translation = teleport_hitbox->get_position();
	AddChild(teleport_button);
	m_button_vec.push_back(teleport_button);
	
	auto background_background = std::make_shared<Util::GameObject>();
	background_background->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/wood_background.png"));
	background_background->SetZIndex(-1);
	AddChild(background_background);
	background_background->m_Transform.translation = {420,0};
}

void MapSelector::update() {
	// get mouse pos
	auto mouse_ptsd_pos = Util::Input::GetCursorPosition();
	glm::vec2 mouse_pos = {
		 mouse_ptsd_pos.x,
		-mouse_ptsd_pos.y
	};

	bool LB = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);
	
	for (auto& clickable: m_clickable_vec) {
		if (!LB) break;

		// breaks when a clickable is successfully clicked
		if (clickable->process_click(mouse_pos)) break;
	}

	// map background change
	peaceful_button->update(mouse_pos, LB);
	ice_button->update(mouse_pos, LB);
	teleport_button->update(mouse_pos, LB);
	summon_button->update(mouse_pos, LB);
	
	if (peaceful_button->get_button_state() == layout::BUTTON_STATE::HOVER) {
		RemoveChild(m_background);
		m_background = m_peaceful_background;
		AddChild(m_background);
	}
	if (ice_button->get_button_state() == layout::BUTTON_STATE::HOVER) {
		RemoveChild(m_background);
		m_background = m_ice_background;
		AddChild(m_background);
	}
	if (teleport_button->get_button_state() == layout::BUTTON_STATE::HOVER) {
		RemoveChild(m_background);
		m_background = m_teleport_background;
		AddChild(m_background);
	}
	if (summon_button->get_button_state() == layout::BUTTON_STATE::HOVER) {
		RemoveChild(m_background);
		m_background = m_summon_background;
		AddChild(m_background);
	}
	
	switch (secret_map_state) {
	case 0:
		if (Util::Input::IsKeyUp(Util::Keycode::N)) ++secret_map_state;
	break;
	case 1:
	case 3:
		if (Util::Input::IsKeyUp(Util::Keycode::T)) ++secret_map_state;
	break;
	case 2:
		if (Util::Input::IsKeyUp(Util::Keycode::U)) ++secret_map_state;
	break;
	case 4: case 5:
		if (Util::Input::IsKeyUp(Util::Keycode::O)) ++secret_map_state;
	break;
	case 6:
		if (Util::Input::IsKeyUp(Util::Keycode::P)) ++secret_map_state;
	break;
	case 7:
		if (Util::Input::IsKeyUp(Util::Keycode::L)) ++secret_map_state;
	break;
	default: ;
	}
	
	if (secret_map_state == 8) {
		m_spawn_map_type = CONSTANTS::TYPE::MAP::SECRET;
		has_map = true;
	}
}

CONSTANTS::TYPE::MAP MapSelector::get_map_type() {
	secret_map_state = 0;
	has_map = false;
	
	return m_spawn_map_type;
}

}
