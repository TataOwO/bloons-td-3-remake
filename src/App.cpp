#include "App.hpp"

#include "Constants.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
	LOG_TRACE("Start");
	
	switch (m_current_game_state) {
	case GameState::MAP_SELECTOR:
		m_render_manager->AddChild(m_map_selector);
	break;
	case GameState::MAIN_GAME:
		m_render_manager->AddChild(m_main_game);
		m_main_game->init(m_map_selector->get_map_type());
	break;
	default: break;
	}
}

void App::Update() {
	switch (m_current_game_state) {
	case GameState::MAP_SELECTOR:
		m_map_selector->update();
		if (m_map_selector->should_switch()) {
			m_CurrentState = State::START;
			m_current_game_state = GameState::MAIN_GAME;
			m_render_manager->RemoveChild(m_map_selector);
		}
	break;
	case GameState::MAIN_GAME:
		m_main_game->update();
		if (m_main_game->should_select_map()) {
			m_CurrentState = State::START;
			m_current_game_state = GameState::MAP_SELECTOR;
			m_render_manager->RemoveChild(m_main_game);
		}
		if (m_main_game->should_exit_game()) {
			m_CurrentState = State::END;
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