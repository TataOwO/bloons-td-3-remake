#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include "Util/GameObject.hpp"

namespace map::implementation {class BaseMap;}
namespace handlers {class MonkeyManager;};
namespace handlers {class BloonManager;};
namespace handlers {class ProjectileManager;};
namespace handlers {class ClickHandler;};
namespace layout {class GameText;};

namespace logics {

class MainGame final : public Util::GameObject {
public:
	MainGame();
	void init(const std::shared_ptr<map::implementation::BaseMap>& map);
	void update();
	
	bool should_select_map() const;
	bool should_exit_game() const;
private:
	unsigned long long game_tick = 0;
	unsigned int wave = 1;

	std::shared_ptr<map::implementation::BaseMap> m_map;

	// monkey manager
	std::shared_ptr<handlers::MonkeyManager> m_monkey_manager;

	// bloon manager
	std::shared_ptr<handlers::BloonManager> m_bloon_manager;

	// projectiles
	std::shared_ptr<handlers::ProjectileManager> m_projectile_manager;

	// clicks
	std::shared_ptr<handlers::ClickHandler> m_click_handler;

	// TODO: UI
	std::shared_ptr<layout::GameText> m_hp_text;
	std::shared_ptr<layout::GameText> m_money_text;
};

}

#endif