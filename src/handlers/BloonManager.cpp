#include "handlers/BloonManager.hpp"
#include <algorithm>
#include <cstdlib>

namespace handlers {

BloonManager::BloonManager(std::shared_ptr<Util::Renderer> render_manager,
						   std::shared_ptr<handlers::PathManager> path_manager)
	: m_render_manager(std::move(render_manager)),
	  m_path_manager(std::move(path_manager)) {
}

void BloonManager::update(int current_tick, int& game_hp, int& money, bool& money_changed) {
	// Process any scheduled spawns for this tick
	process_spawn_queue(current_tick);

	// Update all active bloons
	for (auto& bloon : m_active_bloons) {
		bloon->update();

		// Check if bloon reached the end
		auto typed_bloon = std::dynamic_pointer_cast<bloons::Bloon>(bloon);
		if (typed_bloon && typed_bloon->is_at_end()) {
			game_hp -= typed_bloon->get_hp();
			money_changed = true;
			m_removal_queue.push_back(bloon);
		}

		// Check if bloon has no HP left
		if (typed_bloon && !typed_bloon->has_hp_left()) {
			handle_bloon_destruction(typed_bloon);
			m_removal_queue.push_back(bloon);
		}
	}

	// Process removals (after iteration is complete)
	process_removal_queue();

	// Update sorted lists for targeting
	update_sorted_lists();
}

void BloonManager::add_bloon(std::shared_ptr<bloons::Bloon> bloon) {
	m_active_bloons.push_back(bloon);
	m_render_manager->AddChild(bloon);
}

void BloonManager::schedule_bloon_spawn(bloons::BLOON_TYPE type, int ticks_until_spawn) {
	m_spawn_queue.push(BloonSpawnInfo(type, ticks_until_spawn));
}

void BloonManager::spawn_random_bloon() {
	// Array of possible bloon types
	std::vector<bloons::BLOON_TYPE> types = {
		bloons::BLOON_TYPE::RED,
		bloons::BLOON_TYPE::BLUE,
		bloons::BLOON_TYPE::GREEN,
		bloons::BLOON_TYPE::YELLOW,
		bloons::BLOON_TYPE::WHITE,
		bloons::BLOON_TYPE::BLACK,
		bloons::BLOON_TYPE::LEAD,
		bloons::BLOON_TYPE::RAINBOW,
		bloons::BLOON_TYPE::CERAMIC
	};

	// Select random bloon type
	bloons::BLOON_TYPE selected_type = types.at(std::rand() % types.size());

	// Get random path for spawning
	auto spawn_route = m_path_manager->get_random_route_path()->get_start_route();

	// Create and add the new bloon
	auto new_bloon = std::make_shared<bloons::Bloon>(spawn_route, selected_type);
	add_bloon(new_bloon);
}

void BloonManager::damage_bloon(std::shared_ptr<bloons::BaseBloon> bloon, int damage) {
	// Apply damage to the bloon
	bloon->handle_take_damage(damage);

	// Check if the bloon is now destroyed
	auto typed_bloon = std::dynamic_pointer_cast<bloons::Bloon>(bloon);
	if (typed_bloon && !typed_bloon->has_hp_left()) {
		// Queue for removal (don't remove during iteration)
		m_removal_queue.push_back(bloon);

		// Handle special destruction effects (like spawning child bloons)
		handle_bloon_destruction(typed_bloon);
	}
}

const std::vector<std::shared_ptr<bloons::BaseBloon>>& BloonManager::get_bloons_by_front() const {
	return m_bloons_by_front;
}

const std::vector<std::shared_ptr<bloons::BaseBloon>>& BloonManager::get_bloons_by_back() const {
	return m_bloons_by_back;
}

const std::vector<std::shared_ptr<bloons::BaseBloon>>& BloonManager::get_bloons_by_hp() const {
	return m_bloons_by_hp;
}

const std::vector<std::shared_ptr<bloons::BaseBloon>>& BloonManager::get_all_bloons() const {
	return m_active_bloons;
}

void BloonManager::clear() {
	// Remove all bloons from the renderer
	for (auto& bloon : m_active_bloons) {
		m_render_manager->RemoveChild(bloon);
	}

	// Clear all containers
	m_active_bloons.clear();
	m_removal_queue.clear();
	m_bloons_by_front.clear();
	m_bloons_by_back.clear();
	m_bloons_by_hp.clear();

	// Clear spawn queue (by recreating it)
	m_spawn_queue = std::priority_queue<BloonSpawnInfo, std::vector<BloonSpawnInfo>, std::greater<BloonSpawnInfo>>();
}

void BloonManager::process_removal_queue() {
	for (auto& bloon : m_removal_queue) {
		// Remove from renderer
		m_render_manager->RemoveChild(bloon);

		// Remove from active bloons
		auto it = std::find(m_active_bloons.begin(), m_active_bloons.end(), bloon);
		if (it != m_active_bloons.end()) {
			m_active_bloons.erase(it);
		}
	}

	// Clear the removal queue
	m_removal_queue.clear();
}

void BloonManager::handle_bloon_destruction(std::shared_ptr<bloons::BaseBloon> bloon) {
	// Handle special effects based on bloon type
	switch (bloon->get_type()) {
	case bloons::BLOON_TYPE::CERAMIC: {
		// ceramic bloons spawn 4 rainbow bloons when destroyed
		for (int i = 0; i < 4; ++i) {
			// Get the bloon's current position and path
			auto current_route = bloon->get_current_route();
			if (!current_route) {
				// If the bloon has reached the end, don't spawn children
				continue;
			}

			// Create rainbow bloon at the same position
			auto rainbow_bloon = std::make_shared<bloons::Bloon>(current_route, bloons::BLOON_TYPE::RAINBOW);
			rainbow_bloon->m_Transform.translation = bloon->get_pos();

			// Add the new bloon
			add_bloon(rainbow_bloon);
		}
	}
	break;
	case bloons::BLOON_TYPE::RAINBOW: {
		// Rainbow bloons spawn 2 white or black bloons
		for (int i = 0; i < 2; ++i) {
			auto current_route = bloon->get_current_route();
			if (!current_route) continue;

			// Randomly choose white or black
			bloons::BLOON_TYPE child_type = (std::rand() % 2 == 0) ?
				bloons::BLOON_TYPE::WHITE : bloons::BLOON_TYPE::BLACK;

			auto child_bloon = std::make_shared<bloons::Bloon>(current_route, child_type);
			child_bloon->m_Transform.translation = bloon->get_pos();

			add_bloon(child_bloon);
		}
	}
	break;
	default:
	break;
	}
}

void BloonManager::process_spawn_queue(int current_tick) {
	// Process all bloons scheduled for this tick or earlier
	while (!m_spawn_queue.empty() && m_spawn_queue.top().spawn_tick <= current_tick) {
		auto spawn_info = m_spawn_queue.top();
		m_spawn_queue.pop();

		// Get a random route for spawning
		auto spawn_route = m_path_manager->get_random_route_path()->get_start_route();

		// Create and add the new bloon
		auto new_bloon = std::make_shared<bloons::Bloon>(spawn_route, spawn_info.type);
		add_bloon(new_bloon);
	}
}

void BloonManager::update_sorted_lists() {
	// Copy active bloons to sorted lists
	m_bloons_by_front = m_active_bloons;
	m_bloons_by_back = m_active_bloons;
	m_bloons_by_hp = m_active_bloons;

	// Sort by distance to front (closest to exit first)
	std::sort(m_bloons_by_front.begin(), m_bloons_by_front.end(),
		[](const std::shared_ptr<bloons::BaseBloon>& a, const std::shared_ptr<bloons::BaseBloon>& b) {
			return a->get_length_to_exit() < b->get_length_to_exit();
		});

	// Sort by distance to back (furthest from exit first)
	std::sort(m_bloons_by_back.begin(), m_bloons_by_back.end(),
		[](const std::shared_ptr<bloons::BaseBloon>& a, const std::shared_ptr<bloons::BaseBloon>& b) {
			return a->get_length_to_exit() > b->get_length_to_exit();
		});

	// Sort by HP (highest HP first)
	std::sort(m_bloons_by_hp.begin(), m_bloons_by_hp.end(),
		[](const std::shared_ptr<bloons::BaseBloon>& a, const std::shared_ptr<bloons::BaseBloon>& b) {
			return a->get_hp() > b->get_hp();
		});
}

}