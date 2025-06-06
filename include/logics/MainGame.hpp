#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include "Util/GameObject.hpp"
#include "CONSTANTS/TYPE.hpp"

namespace map::implementation {class BaseMap;}
namespace handlers {class MonkeyManager;};
namespace handlers {class BloonManager;};
namespace handlers {class ProjectileManager;};
namespace handlers {class ClickHandler;};
namespace handlers {class BloonWaveManager;};
namespace layout {class GameText;};

namespace logics {

class MainGame final : public Util::GameObject {
public:
	MainGame();
	void init(const CONSTANTS::TYPE::MAP& map_type);
	void update();
	
	CONSTANTS::TYPE::GAME_STATE get_next_game_state() const {return m_game_next_state;};
	CONSTANTS::TYPE::END_SCREEN get_end_screen_state() const {return m_player_won_state;};
private:
	unsigned long long game_tick = 0;
	unsigned int wave = 1;

	std::shared_ptr<map::implementation::BaseMap> m_map;

	// monkey manager
	std::shared_ptr<handlers::MonkeyManager> m_monkey_manager;

	// bloon manager
	std::shared_ptr<handlers::BloonManager> m_bloon_manager;
	std::shared_ptr<handlers::BloonWaveManager> m_wave_manager;

	// projectiles
	std::shared_ptr<handlers::ProjectileManager> m_projectile_manager;

	// clicks
	std::shared_ptr<handlers::ClickHandler> m_click_handler;

	// determines what the next screen would be
	CONSTANTS::TYPE::GAME_STATE m_game_next_state = CONSTANTS::TYPE::GAME_STATE::NO_CHANGE;
	CONSTANTS::TYPE::END_SCREEN m_player_won_state = CONSTANTS::TYPE::END_SCREEN::WON;
	
	// help
	std::shared_ptr<Util::GameObject> m_help_screen;
	bool m_help_screen_display = false;

	// TODO: UI
	std::shared_ptr<layout::GameText> m_hp_text;
	std::shared_ptr<layout::GameText> m_money_text;
	std::shared_ptr<layout::GameText> m_wave_text;
};

}

#endif