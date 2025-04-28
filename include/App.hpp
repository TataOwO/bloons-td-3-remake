#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Text.hpp"
#include "Util/Renderer.hpp"

#include "map/route/Route.hpp"
#include "map/MapBackground.hpp"
#include "hitboxes/CircularHitbox.hpp"

#include "utility/functions.hpp"
#include "layout/GameText.hpp"

#include "handlers/PathManager.hpp"
#include "handlers/MonkeyManager.hpp"
#include "handlers/BloonManager.hpp"
#include "handlers/ProjectileManager.hpp"
#include "handlers/ClickHandler.hpp"

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
	void ValidTask();

	std::shared_ptr<Util::Renderer> m_render_manager = std::make_shared<Util::Renderer>();

	unsigned long long game_tick = 0;

	// TODO: map object
	map::MapBackground background = map::MapBackground();
	std::vector<std::string> background_images = {
		RESOURCE_DIR"/images/maps/ice_map.png",
		RESOURCE_DIR"/images/maps/ice_map_frozen.png",
		RESOURCE_DIR"/images/maps/ice_map_sleeping_frog.png"
	};

	std::shared_ptr<handlers::PathManager> m_path_manager;

	// monkey manager
	std::shared_ptr<handlers::MonkeyManager> m_monkey_manager;

	// bloon manager
	std::shared_ptr<handlers::BloonManager> m_bloon_manager;

	// projectiles
	std::shared_ptr<handlers::ProjectileManager> m_projectile_manager;

	// clicks
	std::shared_ptr<handlers::ClickHandler> m_click_handler;

	// TODO: UI
	std::shared_ptr<layout::GameText> m_hp_text = std::make_shared<layout::GameText>("HP", 30);
	std::shared_ptr<layout::GameText> m_money_text = std::make_shared<layout::GameText>("money", 30);

private:
	State m_CurrentState = State::START;
};

#endif