#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
	LOG_TRACE("Start");
	
	switch (m_current_game_state) {
	case CONSTANTS::TYPE::GAME_STATE::MAP_SELECTOR:
		m_render_manager->AddChild(m_map_selector);
	break;
	case CONSTANTS::TYPE::GAME_STATE::MAIN_GAME:
		m_render_manager->AddChild(m_main_game);
		m_main_game->init(m_current_map_type);
	break;
	case CONSTANTS::TYPE::GAME_STATE::GAME_END_SCREEN:
		m_render_manager->AddChild(m_end_screen);
		m_end_screen->init(m_end_screen_state, m_current_map_type); // get param from main game
	break;
	case CONSTANTS::TYPE::GAME_STATE::EXIT_GAME:
		set_state(State::END);
	break;
	default: break;
	}
}

void App::Update() {
	switch (m_current_game_state) {
	case CONSTANTS::TYPE::GAME_STATE::MAP_SELECTOR: {
		m_map_selector->update();
		if (m_map_selector->should_switch()) {
			m_CurrentState = State::START;
			m_current_game_state = CONSTANTS::TYPE::GAME_STATE::MAIN_GAME;
			m_render_manager->RemoveChild(m_map_selector);
			m_current_map_type = m_map_selector->get_map_type();
		}
	}
	break;
	case CONSTANTS::TYPE::GAME_STATE::MAIN_GAME: {
		m_main_game->update();
		auto state = m_main_game->get_next_game_state();
		if (state != CONSTANTS::TYPE::GAME_STATE::NO_CHANGE) {
			m_CurrentState = State::START;
			m_current_game_state = state;
			m_end_screen_state = m_main_game->get_end_screen_state();
			m_render_manager->RemoveChild(m_main_game);
		}
	}
	break;
	case CONSTANTS::TYPE::GAME_STATE::GAME_END_SCREEN: {
		m_end_screen->update();
		auto state = m_end_screen->get_next_game_state();
		if (state != CONSTANTS::TYPE::GAME_STATE::NO_CHANGE) {
			m_CurrentState = State::START;
			m_current_game_state = state;
			m_render_manager->RemoveChild(m_end_screen);
		}
	}
	break;
	default: break;
	}
	
	m_render_manager->Update();

	/*
	 * Do not touch the code below as they serve the purpose for
	 * closing the window.
	 */
	if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
		m_CurrentState = State::END;
	}
}

void App::End() { // NOLINT(this method will mutate members in the future)
	LOG_TRACE("End");
}