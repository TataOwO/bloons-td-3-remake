#include "logics/EndScreen.hpp"

#include <iostream>

#include "CONSTANTS/TYPE.hpp"
#include "hitboxes/RectangularHitbox.hpp"
#include "layout/Button.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "CONSTANTS/Z_INDEX.hpp"

namespace logics {

EndScreen::EndScreen() {
	SetZIndex(CONSTANTS::Z_INDEX::ESCAPE_MENU);
	
	// retry button
	m_retry_button = std::make_shared<layout::Button>();
	m_retry_button = std::make_shared<layout::Button>();
	m_retry_button->m_Transform.translation = {-215,-270};
	m_retry_button->SetZIndex(CONSTANTS::Z_INDEX::ESCAPE_BUTTON);
	// retry button hitbox
	m_retry_button->set_hitbox(std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{-215,-270},glm::vec2{270,62},0));
	// on click
	m_retry_button->set_on_click([ngs=&m_next_game_state]() {
		*ngs = CONSTANTS::TYPE::GAME_STATE::MAIN_GAME;
		std::cout << "retry button clicked" << std::endl;
		return true;
	});
	// retry button drawable
	m_retry_button->set_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/end_screen/retry.png"));
	m_retry_button->set_hover_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/end_screen/retry_hover.png"));
	// add to children
	AddChild(m_retry_button);
	m_retry_button->SetVisible(true);
	
	// menu button
	m_menu_button = std::make_shared<layout::Button>();
	m_menu_button = std::make_shared<layout::Button>();
	m_menu_button->m_Transform.translation = {215,-270};
	m_menu_button->SetZIndex(CONSTANTS::Z_INDEX::ESCAPE_BUTTON);
	// menu button hitbox
	m_menu_button->set_hitbox(std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{215,-270},glm::vec2{270,62},0));
	// on click
	m_menu_button->set_on_click([ngs=&m_next_game_state]() {
		*ngs = CONSTANTS::TYPE::GAME_STATE::MAP_SELECTOR;
		std::cout << "main menu button clicked" << std::endl;
		return true;
	});
	// menu button drawable
	m_menu_button->set_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/end_screen/main_menu.png"));
	m_menu_button->set_hover_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/end_screen/main_menu_hover.png"));
	// add to children
	AddChild(m_menu_button);
	m_menu_button->SetVisible(true);
}

void EndScreen::init(const CONSTANTS::TYPE::END_SCREEN& end_screen_state, const CONSTANTS::TYPE::MAP& map_type) {
	switch (end_screen_state) {
	case CONSTANTS::TYPE::END_SCREEN::WON:
		SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/end_screen_win.png"));
	break;
	case CONSTANTS::TYPE::END_SCREEN::FAILED:
		SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/end_screen_lose.png"));
	break;
	default: break;
	}
	
	if (map_type == CONSTANTS::TYPE::MAP::SECRET) m_retry_button->disable();
	else m_retry_button->enable();
	
	m_next_game_state = CONSTANTS::TYPE::GAME_STATE::NO_CHANGE;
}

void EndScreen::update() const {
	// get mouse pos
	auto mouse_ptsd_pos = Util::Input::GetCursorPosition();
	glm::vec2 mouse_pos = {
		 mouse_ptsd_pos.x,
		-mouse_ptsd_pos.y
	};
	bool LB = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);
	
	m_retry_button->update(mouse_pos, LB);
	m_menu_button ->update(mouse_pos, LB);
}

}
