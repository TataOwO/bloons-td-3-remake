#include "handlers/BloonManager.hpp"
#include <algorithm>
#include <cstdlib>

#include "handlers/PathManager.hpp"
#include "Util/Renderer.hpp"

#include "bloons/BaseBloon.hpp"

#include "bloons/Bloon.hpp"
#include "layout/GameText.hpp"
#include "map/route/RoutePath.hpp"
#include "map/route/Route.hpp"

namespace handlers {

BloonManager::BloonManager() {
}

void BloonManager::update(const std::shared_ptr<handlers::PathManager>& path_manager, int current_tick, const std::shared_ptr<layout::GameText> &game_hp) {
	// Process any scheduled spawns for this tick
	process_spawn_queue(path_manager, current_tick);

	std::vector<std::shared_ptr<bloons::BaseBloon>> should_spawn_children = {};

	// Update all active bloons
	for (auto&bloon: m_active_bloons) {
		bloon->update();

		bool should_remove = false;

		// Check if bloon reached the end
		if (bloon->is_at_end()) {
			game_hp->sub_value(bloon->get_hp());
			should_remove = true;
		}

		// Check if bloon has no HP left
		if (!should_remove && !bloon->has_hp_left()) {
			should_spawn_children.push_back(bloon);
			should_remove = true;
		}

		// Remove the bloon if needed
		if (should_remove) m_removal_queue.push_back(bloon);
	}

	for (auto& bloon: should_spawn_children) {
		handle_bloon_destruction(bloon);
	}

	//remove bloons
	process_removal_queue();
}

void BloonManager::add_bloon(const std::shared_ptr<bloons::BaseBloon> &bloon) {
	// Add to active bloons
	m_active_bloons.push_back(bloon);

	// Add to renderer
	AddChild(bloon);

	// Insert into sorted lists
	insert_into_sorted_lists(bloon);
}

bool BloonManager::is_completely_empty() const {
	return m_active_bloons.empty() && m_bloons_by_front.empty() && m_bloons_by_back.empty() && m_bloons_by_hp.empty() && m_spawn_queue.empty();
}

void BloonManager::schedule_bloon_spawn(CONSTANTS::TYPE::BLOON type, int ticks_until_spawn) {
	int spawn_tick = ticks_until_spawn;
	m_spawn_queue.emplace(type, spawn_tick);
}

void BloonManager::spawn_random_bloon(const std::shared_ptr<map::route::Route> &spawn_route) {
	// Array of possible bloon types
	std::vector<CONSTANTS::TYPE::BLOON> types = {
		CONSTANTS::TYPE::BLOON::RED,
		CONSTANTS::TYPE::BLOON::BLUE,
		CONSTANTS::TYPE::BLOON::GREEN,
		CONSTANTS::TYPE::BLOON::YELLOW,
		CONSTANTS::TYPE::BLOON::WHITE,
		CONSTANTS::TYPE::BLOON::BLACK,
		CONSTANTS::TYPE::BLOON::LEAD,
		CONSTANTS::TYPE::BLOON::RAINBOW,
		CONSTANTS::TYPE::BLOON::CERAMIC
	};

	// Select random bloon type
	CONSTANTS::TYPE::BLOON selected_type = types.at(std::rand() % types.size());

	// Create and add the new bloon
	auto new_bloon = std::make_shared<bloons::Bloon>(spawn_route, selected_type);
	add_bloon(new_bloon);
}

void BloonManager::damage_bloon(const std::shared_ptr<bloons::BaseBloon> &bloon, int damage) {
	// Apply damage to the bloon
	bloon->handle_take_damage(damage);

	// Check if the bloon is now destroyed
	if (!bloon->has_hp_left()) {
		// Queue for removal (don't remove during iteration)
		m_removal_queue.push_back(bloon);

		// Handle special destruction effects (like spawning child bloons)
		handle_bloon_destruction(bloon);
	}
}

const std::vector<std::shared_ptr<bloons::BaseBloon>>& BloonManager::get_bloons_by_front() const {
	return m_bloons_by_front;
}

const std::vector<std::shared_ptr<bloons::BaseBloon>>& BloonManager::get_bloons_by_back() const {
	return m_bloons_by_back;
}

const std::vector<std::shared_ptr<bloons::BaseBloon>>& BloonManager::get_bloons_by_strong() const {
	return m_bloons_by_hp;
}

int BloonManager::get_accumulated_money() {
	int ret_money = 0;
	for (auto& bloon: m_active_bloons) {
		ret_money += bloon->get_accumulated_money();
		bloon->reset_accumulated_money();
	}
	return ret_money;
}

void BloonManager::clear() {
	// Remove all bloons from the renderer
	for (auto& bloon : m_active_bloons) {
		RemoveChild(bloon);
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
		RemoveChild(bloon);

		// Remove from each sorted list
		remove_from_sorted_lists(bloon);

		// Remove from active bloons
		auto it = std::find(m_active_bloons.begin(), m_active_bloons.end(), bloon);
		if (it != m_active_bloons.end()) {
			m_active_bloons.erase(it);
		}
	}

	// clear the removal queue
	m_removal_queue.clear();
}

void BloonManager::handle_bloon_destruction(const std::shared_ptr<bloons::BaseBloon> &bloon) {
	auto current_route = bloon->get_current_route();
	if (!current_route) return;
	
	// Handle special effects based on bloon type
	switch (bloon->get_type()) {
	case CONSTANTS::TYPE::BLOON::CERAMIC: {
		// ceramic bloons spawn 4 rainbow bloons when destroyed
		spawn_child_bloons(bloon, CONSTANTS::TYPE::BLOON::RAINBOW, 4);
	}
	break;
	case CONSTANTS::TYPE::BLOON::RAINBOW: {
		// Rainbow bloons spawn 2 white or black bloons
		for (int i = 0; i < 2; ++i) {
			// Randomly choose white or black
			CONSTANTS::TYPE::BLOON child_type = (std::rand() % 2 == 0) ?
				CONSTANTS::TYPE::BLOON::WHITE : CONSTANTS::TYPE::BLOON::BLACK;

			spawn_child_bloon(bloon, child_type);
		}
	}
	break;
	default:
	break;
	}
}

void BloonManager::spawn_child_bloons(const std::shared_ptr<bloons::BaseBloon> &parent, CONSTANTS::TYPE::BLOON child_type, int count) {
	auto current_route = parent->get_current_route();
	if (!current_route) {
		// If the bloon has reached the end, don't spawn children
		return;
	}

	for (int i = 0; i < count; ++i) {
		spawn_child_bloon(parent, child_type);
	}
}

void BloonManager::spawn_child_bloon(const std::shared_ptr<bloons::BaseBloon> &parent, CONSTANTS::TYPE::BLOON child_type) {
	auto current_route = parent->get_current_route();
	if (!current_route) return;

	// Create child bloon at the same position
	auto child_bloon = std::make_shared<bloons::Bloon>(current_route, child_type);
	child_bloon->m_Transform.translation = parent->get_pos();

	// Add the new bloon
	add_bloon(child_bloon);
}

void BloonManager::process_spawn_queue(const std::shared_ptr<handlers::PathManager> &path_manager, int current_tick) {
	// Process all bloons scheduled for this tick or earlier
	while (!m_spawn_queue.empty() && m_spawn_queue.top().spawn_tick <= current_tick) {
		auto spawn_info = m_spawn_queue.top();
		m_spawn_queue.pop();

		// Get a random route for spawning
		auto spawn_route = path_manager->get_random_route_path()->get_start_route();

		// Create and add the new bloon
		auto new_bloon = std::make_shared<bloons::Bloon>(spawn_route, spawn_info.type);
		add_bloon(new_bloon);
	}
}

void BloonManager::insert_into_sorted_lists(const std::shared_ptr<bloons::BaseBloon> &bloon) {
	// Insert into front list (sorted by distance to exit, closest first)
	auto front_pos = std::lower_bound(m_bloons_by_front.begin(), m_bloons_by_front.end(), bloon,
		[](const std::shared_ptr<bloons::BaseBloon>& a, const std::shared_ptr<bloons::BaseBloon>& b) {
			return a->get_length_to_exit() < b->get_length_to_exit();
		});
	m_bloons_by_front.insert(front_pos, bloon);

	// Insert into back list (sorted by distance to exit, furthest first)
	auto back_pos = std::lower_bound(m_bloons_by_back.begin(), m_bloons_by_back.end(), bloon,
		[](const std::shared_ptr<bloons::BaseBloon>& a, const std::shared_ptr<bloons::BaseBloon>& b) {
			return a->get_length_to_exit() > b->get_length_to_exit();
		});
	m_bloons_by_back.insert(back_pos, bloon);

	// Insert into hp list (sorted by type priority)
	auto hp_pos = std::lower_bound(m_bloons_by_hp.begin(), m_bloons_by_hp.end(), bloon,
		[](const std::shared_ptr<bloons::BaseBloon>& a, const std::shared_ptr<bloons::BaseBloon>& b) {
			// Define ordering of bloon types
			const std::map<CONSTANTS::TYPE::BLOON, int> type_priority = {
				{CONSTANTS::TYPE::BLOON::MOAB,    10},
				{CONSTANTS::TYPE::BLOON::CERAMIC, 9},
				{CONSTANTS::TYPE::BLOON::RAINBOW, 8},
				{CONSTANTS::TYPE::BLOON::LEAD,    7},
				{CONSTANTS::TYPE::BLOON::BLACK,   6},
				{CONSTANTS::TYPE::BLOON::WHITE,   5},
				{CONSTANTS::TYPE::BLOON::YELLOW,  4},
				{CONSTANTS::TYPE::BLOON::GREEN,   3},
				{CONSTANTS::TYPE::BLOON::BLUE,    2},
				{CONSTANTS::TYPE::BLOON::RED,     1},
			};

			// Get priorities for the bloon types
			int priority_a = type_priority.at(a->get_type());
			int priority_b = type_priority.at(b->get_type());

			// If same type, sort by progress (closer to exit first)
			if (priority_a == priority_b) {
				return a->get_length_to_exit() < b->get_length_to_exit();
			}

			// Otherwise sort by type priority (higher first)
			return priority_a > priority_b;
		});
	m_bloons_by_hp.insert(hp_pos, bloon);
}

void BloonManager::remove_from_sorted_lists(const std::shared_ptr<bloons::BaseBloon> &bloon) {
	// Helper lambda to remove from a specific sorted list
	auto remove_from_list = [&](std::vector<std::shared_ptr<bloons::BaseBloon>>& list) {
		auto it = std::find(list.begin(), list.end(), bloon);
		if (it != list.end()) {
			list.erase(it);
		}
	};

	// Remove from each sorted list
	remove_from_list(m_bloons_by_front);
	remove_from_list(m_bloons_by_back);
	remove_from_list(m_bloons_by_hp);
}

BloonManager::~BloonManager() {
	
}

}
