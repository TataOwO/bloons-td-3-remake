#ifndef APP_HPP
#define APP_HPP

#include "Util/Renderer.hpp"

#include "logics/MainGame.hpp"
#include "logics/MapSelector.hpp"
#include "logics/EndScreen.hpp"
#include "CONSTANTS/TYPE.hpp"

class App {
public:
	enum class State {
		START,
		UPDATE,
		END,
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
	std::shared_ptr<logics::EndScreen> m_end_screen = std::make_shared<logics::EndScreen>();

private:
	State m_CurrentState = State::START;
	// next game state
	CONSTANTS::TYPE::GAME_STATE m_current_game_state = CONSTANTS::TYPE::GAME_STATE::MAP_SELECTOR;
	// end screen state
	CONSTANTS::TYPE::END_SCREEN m_end_screen_state = CONSTANTS::TYPE::END_SCREEN::WON;
	// selected map
	CONSTANTS::TYPE::MAP m_current_map_type = CONSTANTS::TYPE::MAP::PEACEFUL;
};

#endif