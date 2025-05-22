#ifndef APP_HPP
#define APP_HPP

#include "Util/Renderer.hpp"

#include "logics/MainGame.hpp"
#include "logics/MapSelector.hpp"

class App {
public:
	enum class State {
		START,
		UPDATE,
		END,
	};
	
	enum class GameState {
		MAP_SELECTOR,
		MAIN_GAME,
	};

	void set_state(const State& s) {m_CurrentState = s;}

	State GetCurrentState() const { return m_CurrentState; }

	void Start();
	
	void Update();

	void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
	unsigned char esc_hold_time = 0;

	void ValidTask();

	std::shared_ptr<Util::Renderer> m_render_manager = std::make_shared<Util::Renderer>();

	std::shared_ptr<logics::MainGame> m_main_game = std::make_shared<logics::MainGame>();
	std::shared_ptr<logics::MapSelector> m_map_selector = std::make_shared<logics::MapSelector>();

private:
	State m_CurrentState = State::START;
	GameState m_current_game_state = GameState::MAP_SELECTOR;
};

#endif