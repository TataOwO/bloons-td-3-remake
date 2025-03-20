#ifndef APP_HPP
#define APP_HPP

#include <iostream>

#include "pch.hpp" // IWYU pragma: export

#include "Util/Text.hpp"
#include "Util/Color.hpp"

#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"
#include "Util/Renderer.hpp"
#include "monkeys/DartMonkey.hpp"
#include "bloons/Bloon.hpp"

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

	Util::Renderer m_render_manager;

	int game_tick = 0;
	int game_hp = 200;

	std::vector<std::shared_ptr<map::route::Route>> m_route_vec;

	std::shared_ptr<map::route::RoutePath> m_route_path;

	// TODO: monkey manager
	std::vector<std::shared_ptr<monkeys::DartMonkey>> m_monkey_vec;

	// TODO: bloons manager
	std::vector<std::shared_ptr<bloons::Bloon>> bloon_vec = {};

	// TODO: menu
	std::string font_name = "Arial";
	Util::Color text_color = Util::Color(255,255,255);
	std::string game_hp_string = "200";
	
	std::shared_ptr<Util::Text> hp_display;
	
private:
    State m_CurrentState = State::START;
};

#endif
