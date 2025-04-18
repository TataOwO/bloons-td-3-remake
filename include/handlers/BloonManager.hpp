#ifndef BLOON_MANAGER_HPP
#define BLOON_MANAGER_HPP

#include <vector>
#include <map>
#include <queue>
#include <memory>

#include "PathManager.hpp"
#include "Util/Renderer.hpp"

#include "bloons/BaseBloon.hpp"
#include "bloons/Bloon.hpp"

namespace handlers {

// bloon spawn struct
struct BloonSpawnInfo {
	bloons::BLOON_TYPE type;
	int spawn_tick;

	BloonSpawnInfo(bloons::BLOON_TYPE t, int tick) : type(t), spawn_tick(tick) {}

	// for priority queue
	bool operator>(const BloonSpawnInfo& other) const {
		return spawn_tick > other.spawn_tick;
	}
};

class BloonManager {
public:
	BloonManager(std::shared_ptr<Util::Renderer> render_manager, std::shared_ptr<handlers::PathManager> path_manager);

	// process bloon updates
	void update(int current_tick, int& game_hp, bool* money_changed);

	void add_bloon(std::shared_ptr<bloons::BaseBloon> bloon);

	// add bloon spawn to queue
	void schedule_bloon_spawn(bloons::BLOON_TYPE type, int ticks_until_spawn);

	// spawn bloon at random
	void spawn_random_bloon();

	void damage_bloon(std::shared_ptr<bloons::BaseBloon> bloon, int damage);

	// for 3 different monkey targetting
	const std::vector<std::shared_ptr<bloons::BaseBloon>>& get_bloons_by_front() const;
	const std::vector<std::shared_ptr<bloons::BaseBloon>>& get_bloons_by_back() const;
	const std::vector<std::shared_ptr<bloons::BaseBloon>>& get_bloons_by_strong() const;

	// clear all bloons and spawn schedule
	void clear();

	const std::vector<std::shared_ptr<bloons::BaseBloon>>& get_all_bloons() const;

private:
	// removes bloons in the removal queue
	void process_removal_queue();

	// handles destruction effects for the given bloon
	void handle_bloon_destruction(std::shared_ptr<bloons::BaseBloon> bloon);
	
	// Helper methods for spawning child bloons
	void spawn_child_bloons(std::shared_ptr<bloons::BaseBloon> parent, bloons::BLOON_TYPE child_type, int count);
	void spawn_child_bloon(std::shared_ptr<bloons::BaseBloon> parent, bloons::BLOON_TYPE child_type);

	// process the spawn queue for the current tick
	void process_spawn_queue(int current_tick);

	// Maintain sorted lists
	void insert_into_sorted_lists(std::shared_ptr<bloons::BaseBloon> bloon);
	void remove_from_sorted_lists(std::shared_ptr<bloons::BaseBloon> bloon);

	// active bloons (that aren't destroyed)
	std::vector<std::shared_ptr<bloons::BaseBloon>> m_active_bloons = {};

	// bloons marked for removal
	std::vector<std::shared_ptr<bloons::BaseBloon>> m_removal_queue = {};

	// sorted bloon lists for different targeting methods
	std::vector<std::shared_ptr<bloons::BaseBloon>> m_bloons_by_front = {};
	std::vector<std::shared_ptr<bloons::BaseBloon>> m_bloons_by_back = {};
	std::vector<std::shared_ptr<bloons::BaseBloon>> m_bloons_by_hp = {};

	// scheduled bloon spawns using priority queue
	std::priority_queue<BloonSpawnInfo, std::vector<BloonSpawnInfo>, std::greater<BloonSpawnInfo>> m_spawn_queue;

	std::shared_ptr<Util::Renderer> m_render_manager;
	std::shared_ptr<handlers::PathManager> m_path_manager;

// base
public:
	BloonManager(const BloonManager&) = delete;
	BloonManager(BloonManager&&) = delete;
	BloonManager& operator=(const BloonManager&) = delete;
	BloonManager& operator=(BloonManager&&) = delete;
	~BloonManager() = default;
};

}

#endif