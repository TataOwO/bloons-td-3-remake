#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Text.hpp"
#include "Util/Renderer.hpp"

#include "map/route/Route.hpp"
#include "map/MapBackground.hpp"
#include "monkeys/DartMonkey.hpp"
#include "bloons/Bloon.hpp"
#include "projectiles/BaseProjectile.hpp"
#include "hitboxes/CircularHitbox.hpp"

#include "utility/functions.hpp"

#include "handlers/PathManager.hpp"
#include "handlers/MonkeyManager.hpp"
#include "handlers/BloonManager.hpp"
#include "handlers/ProjectileManager.hpp"

class App {
public:
	enum class State {
		START,
		UPDATE,
		END,
	};

	State GetCurrentState() const { return m_CurrentState; }

	void Start();

	void Update();

	void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
	void ValidTask();

	std::shared_ptr<Util::Renderer> m_render_manager = std::make_shared<Util::Renderer>();

	int game_tick = 0;
	int game_hp = 200;
	int money = 100000;
	bool money_changed = false;

	std::shared_ptr<handlers::PathManager> m_path_manager;

	// TODO: map object
	map::MapBackground background = map::MapBackground(0);
	std::vector<std::string> background_images = {
		RESOURCE_DIR"/images/maps/ice_map.png",
		RESOURCE_DIR"/images/maps/ice_map_frozen.png",
		RESOURCE_DIR"/images/maps/ice_map_sleeping_frog.png"
	};

	// monkey manager
	std::shared_ptr<handlers::MonkeyManager> m_monkey_manager;

	// bloon manager
	std::shared_ptr<handlers::BloonManager> m_bloon_manager;

	// projectiles
	std::shared_ptr<handlers::ProjectileManager> m_projectile_manager;

	// TODO: UI
	std::shared_ptr<Util::GameObject> status_display = std::make_shared<Util::GameObject>();
	std::string status_text;
	std::shared_ptr<Util::Text> status_text_obj = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/VeraMono.ttf", 30, "hp: 200\nmoney: 160");

	// TODO: UI
	bool monke_place_hold_has_collision = false;
	std::shared_ptr<Util::GameObject> monkey_place_holder = std::make_shared<Util::GameObject>();
	std::shared_ptr<Util::Image> dart_img = std::make_shared<Util::Image>(RESOURCE_DIR"/images/dart_monkey_1.5.png");
	std::shared_ptr<Util::Image> dart_red = std::make_shared<Util::Image>(RESOURCE_DIR"/images/dart_monkey_RED.png");
	std::shared_ptr<hitboxes::CircularHitbox> monke_placeholder_hitbox = std::make_shared<hitboxes::CircularHitbox>(glm::vec2{0,0}, 30);

private:
	State m_CurrentState = State::START;
};

#endif