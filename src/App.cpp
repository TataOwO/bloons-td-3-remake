#include "App.hpp"

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

	// TODO: MOVE ALL THESE TO MAPS
	// route
	std::vector<std::shared_ptr<map::route::Route>> route_vec1 = {
		std::make_shared<map::route::Route>(glm::vec2(215,0), glm::vec2(157, 158)),
		std::make_shared<map::route::Route>(glm::vec2(157, 158), glm::vec2(406, 57)),
		std::make_shared<map::route::Route>(glm::vec2(406, 57), glm::vec2(443,183)),
		std::make_shared<map::route::Route>(glm::vec2(443,183), glm::vec2(262,209)),
		std::make_shared<map::route::Route>(glm::vec2(262,209), glm::vec2(116,413)),
		std::make_shared<map::route::Route>(glm::vec2(116,413), glm::vec2(316,462)),
		std::make_shared<map::route::Route>(glm::vec2(316,462), glm::vec2(352,453)),
		std::make_shared<map::route::Route>(glm::vec2(352,453), glm::vec2(397,345)),
		std::make_shared<map::route::Route>(glm::vec2(397,345), glm::vec2(537,239)),
		std::make_shared<map::route::Route>(glm::vec2(537,239), glm::vec2(563,195)),
		std::make_shared<map::route::Route>(glm::vec2(563,195), glm::vec2(581,111)),
		std::make_shared<map::route::Route>(glm::vec2(581,111), glm::vec2(632,149)),
		std::make_shared<map::route::Route>(glm::vec2(632,149), glm::vec2(652,215)),
		std::make_shared<map::route::Route>(glm::vec2(652,215), glm::vec2(624,328)),
		std::make_shared<map::route::Route>(glm::vec2(624,328), glm::vec2(572,462)),
		std::make_shared<map::route::Route>(glm::vec2(572,462), glm::vec2(485,460)),
		std::make_shared<map::route::Route>(glm::vec2(485,460), glm::vec2(480,497)),
		std::make_shared<map::route::Route>(glm::vec2(480,497), glm::vec2(428,604)),
		std::make_shared<map::route::Route>(glm::vec2(428,604), glm::vec2(319,573)),
		std::make_shared<map::route::Route>(glm::vec2(319,573), glm::vec2(185,559)),
		std::make_shared<map::route::Route>(glm::vec2(185,559), glm::vec2(82,720)),
	};

	// route paths
	std::vector<std::shared_ptr<map::route::RoutePath>> route_paths = {
		std::make_shared<map::route::RoutePath>(route_vec1),
	};

	// add route paths to manager
	m_path_manager = std::make_shared<map::route::PathManager>(route_paths, m_render_manager);

	// TODO: monkey manager
	// monkeys
	m_monkey_vec = {
		std::make_shared<monkeys::DartMonkey>(glm::vec2(180,-20)),
		std::make_shared<monkeys::DartMonkey>(glm::vec2(-200,10)),
		std::make_shared<monkeys::DartMonkey>(glm::vec2(-120,223)),
	};

	// monkeys
	for (std::shared_ptr<Util::GameObject> monke : m_monkey_vec) {
		m_render_manager->AddChild(monke);
	}

	// background
	background.set_layers(background_images);
	for (auto layer: background.get_layers()) {
		m_render_manager->AddChild(layer);
	}

	// hp display
	hp_display->SetDrawable(hp_text_obj);
	m_render_manager->AddChild(hp_display);
	hp_display->SetZIndex(10);

    m_CurrentState = State::UPDATE;
}

void App::Update() {
	++game_tick;

	// TODO: this is for bloons manager
	if (game_tick%20-10 == 0) {
		std::vector<bloons::BLOON_TYPE> v = {bloons::BLOON_TYPE::RED,bloons::BLOON_TYPE::BLUE,bloons::BLOON_TYPE::GREEN,bloons::BLOON_TYPE::YELLOW,bloons::BLOON_TYPE::WHITE,bloons::BLOON_TYPE::BLACK,bloons::BLOON_TYPE::LEAD,bloons::BLOON_TYPE::RAINBOW,bloons::BLOON_TYPE::CERAMIC};

		bloons::BLOON_TYPE t = v.at(std::rand() % v.size());

		std::shared_ptr<map::route::Route> bloon_spawn_route = m_path_manager->get_random_route_path()->get_start_route();

		std::shared_ptr<bloons::Bloon> new_bloon = std::make_shared<bloons::Bloon>(bloon_spawn_route, t);

		bloon_vec.push_back(new_bloon);
		m_render_manager->AddChild(new_bloon);
	}

	for (auto monke: m_monkey_vec) {
		for (int i=bloon_vec.size()-1; i>=0; --i) {
			std::shared_ptr<bloons::Bloon> bloon = bloon_vec.at(i);
			monke->scan_bloon(bloon);
		}
		monke->attack();

		if (monke->has_projectile()) {
			auto p = monke->get_spawned_projectile();
			projectile_vec.push_back(p);
			m_render_manager->AddChild(p);
		}

		monke->reset_target();
	}

	// TODO: this is for bloons manager
	for (unsigned i=0; i<bloon_vec.size(); ++i) {
		std::shared_ptr<bloons::Bloon> bloon = bloon_vec.at(i);

		bloon->update();

		if (bloon->is_at_end()) {
			game_hp -= bloon->get_hp();
			std::cout << game_hp << std::endl;

			hp_text_obj->SetText(std::to_string(game_hp));

			m_render_manager->RemoveChild(bloon);
			bloon_vec.erase(bloon_vec.begin()+i);
			--i;
		}

		if (!bloon->has_hp_left()) {
			m_render_manager->RemoveChild(bloon);
			bloon_vec.erase(bloon_vec.begin()+i);
			--i;
		}
	}

	
	// projectile collision check
	for (unsigned j=0; j<projectile_vec.size(); ++j) {
		auto p = projectile_vec.at(j);
		p->update();

		for (auto bloon: bloon_vec) {
			if (p->is_collided_with(bloon)) {
				p->deal_damage(bloon);
			}
		}

		if (p->is_dead()) {
			m_render_manager->RemoveChild(p);
			projectile_vec.erase(projectile_vec.begin()+j);
			--j;
		}
	}


    // https://zh.wikipedia.org/zh-tw/%E8%B2%9D%E8%8C%B2%E6%9B%B2%E7%B7%9A
	// curve for boomerang
	m_render_manager->Update();

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
