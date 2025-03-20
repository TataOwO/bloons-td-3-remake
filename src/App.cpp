#include "App.hpp"

#include <iostream>
#include <cstring>

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

	// route
	m_route_vec = {
		std::make_shared<map::route::Route>(glm::vec2(-640, -120), glm::vec2(-520, 120)),
		std::make_shared<map::route::Route>(glm::vec2(-520, 120), glm::vec2(-40, -120)),
		std::make_shared<map::route::Route>(glm::vec2(-40, -120), glm::vec2(80, 120)),
	};

	// route path
	m_route_path = std::make_shared<map::route::RoutePath>(m_route_vec);

	// route path
	std::shared_ptr<Util::GameObject> rp = m_route_path;
	m_render_manager.AddChild(rp);

	// TODO: monkey manager
	// monkeys
	m_monkey_vec = {
		std::make_shared<monkeys::DartMonkey>(glm::vec2(-100,100)),
		std::make_shared<monkeys::DartMonkey>(glm::vec2(-200,300))
	};

	// monkeys
	for (std::shared_ptr<Util::GameObject> monke : m_monkey_vec) {
		m_render_manager.AddChild(monke);
	}

	// hp text
	std::cout << "before text" << std::endl;
	hp_display = std::make_shared<Util::Text>(font_name, 20, game_hp_string);
	std::cout << "after text" << std::endl;
	
	hp_display->SetColor(text_color);

	std::cout << "test" << std::endl;

    m_CurrentState = State::UPDATE;
}

void App::Update() {
	++game_tick;

	// TODO: this is for bloons manager
	if (game_tick%90-60 == 0) {
		std::shared_ptr<bloons::Bloon> new_bloon = std::make_shared<bloons::Bloon>(m_route_path->get_start_route(), bloons::BLOON_TYPE::BLUE);

		bloon_vec.push_back(new_bloon);
		m_render_manager.AddChild(new_bloon);
	}

	// TODO: this is for bloons manager
	for (unsigned i=0; i<bloon_vec.size(); ++i) {
		std::shared_ptr<bloons::Bloon> bloon = bloon_vec.at(i);

		bloon->update();

		if (bloon->is_at_end()) {
			game_hp -= bloon->get_hp();
			// hp_display->SetText(std::to_string(game_hp));
			
			m_render_manager.RemoveChild(bloon);
			bloon_vec.erase(bloon_vec.begin()+i);
			--i;
		}
	}

    // https://zh.wikipedia.org/zh-tw/%E8%B2%9D%E8%8C%B2%E6%9B%B2%E7%B7%9A
	// curve for boomerang
	m_render_manager.Update();

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
