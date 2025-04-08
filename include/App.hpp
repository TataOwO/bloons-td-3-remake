#ifndef APP_HPP
#define APP_HPP

#include <iostream>

#include "pch.hpp" // IWYU pragma: export

#include "Util/Text.hpp"
#include "Util/Color.hpp"
#include "Util/Renderer.hpp"

#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"
#include "map/route/PathManager.hpp"
#include "map/MapBackground.hpp"
#include "monkeys/DartMonkey.hpp"
#include "bloons/Bloon.hpp"
#include "bloons/BaseBloon.hpp"
#include "projectiles/BaseProjectile.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    [[nodiscard]] State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

	std::shared_ptr<Util::Renderer> m_render_manager = std::make_shared<Util::Renderer>();

	int game_tick = 0;
	int game_hp = 200;
	float money = 0;

	std::shared_ptr<map::route::PathManager> m_path_manager;

	// TODO: map object
	map::MapBackground background = map::MapBackground(0);
	std::vector<std::string> background_images = {
		RESOURCE_DIR"/images/maps/ice_map.png",
		RESOURCE_DIR"/images/maps/ice_map_frozen.png",
		RESOURCE_DIR"/images/maps/ice_map_sleeping_frog.png"
	};

	// TODO: monkey manager
	std::vector<std::shared_ptr<monkeys::DartMonkey>> m_monkey_vec;

	// TODO: bloons manager
	std::vector<std::shared_ptr<bloons::Bloon>> bloon_vec = {};

	// projectiles
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> projectile_vec = {};

	// TODO: menu
	std::shared_ptr<Util::GameObject> hp_display = std::make_shared<Util::GameObject>();
	std::shared_ptr<Util::Text> hp_text_obj = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/VeraMono.ttf", 40, "200");

private:
    State m_CurrentState = State::START;
};

#endif
