#ifndef BLOON_MANAGER_HPP
#define BLOON_MANAGER_HPP

#include <queue>
#include "Util/GameObject.hpp"

namespace CONSTANTS::TYPE {enum class BLOON;}
namespace handlers {class PathManager;}
namespace Util     {class Renderer;}
namespace bloons   {class BaseBloon;}
namespace layout   {class GameText;}
namespace map::route {class Route;}

namespace handlers {

// bloon spawn struct
struct BloonSpawnInfo {
	CONSTANTS::TYPE::BLOON type;
	int spawn_tick;

	BloonSpawnInfo(CONSTANTS::TYPE::BLOON t, int tick) : type(t), spawn_tick(tick) {}

	// for priority queue
	bool operator>(const BloonSpawnInfo& other) const {
		return spawn_tick > other.spawn_tick;
	}
};

class BloonManager final : public Util::GameObject {
public:
	BloonManager();

	// process bloon updates
	void update(const std::shared_ptr<handlers::PathManager>& path_manager, int current_tick, const std::shared_ptr<layout::GameText> &game_hp);

	void add_bloon(const std::shared_ptr<bloons::BaseBloon> &bloon);
	bool is_completely_empty() const;

	// add bloon spawn to queue
	void schedule_bloon_spawn(CONSTANTS::TYPE::BLOON type, int ticks_until_spawn);

	// spawn bloon at random
	void spawn_random_bloon(const std::shared_ptr<map::route::Route>& spawn_route);

	void damage_bloon(const std::shared_ptr<bloons::BaseBloon> &bloon, int damage);

	// get the money that all bloons have
	int get_accumulated_money();

	// clear all bloons and spawn schedule
	void clear();

	// for 3 different monkey targeting
	const std::vector<std::shared_ptr<bloons::BaseBloon>>& get_bloons_by_front() const;
	const std::vector<std::shared_ptr<bloons::BaseBloon>>& get_bloons_by_back() const;
	const std::vector<std::shared_ptr<bloons::BaseBloon>>& get_bloons_by_strong() const;

	const std::vector<std::shared_ptr<bloons::BaseBloon>>& get_all_bloons() const {return m_active_bloons;};
private:
	// removes bloons in the removal queue
	void process_removal_queue();

	// handles destruction effects for the given bloon
	void handle_bloon_destruction(const std::shared_ptr<bloons::BaseBloon> &bloon);
	
	// Helper methods for spawning child bloons
	void spawn_child_bloons(const std::shared_ptr<bloons::BaseBloon> &parent, CONSTANTS::TYPE::BLOON child_type, int count);
	void spawn_child_bloon(const std::shared_ptr<bloons::BaseBloon> &parent, CONSTANTS::TYPE::BLOON child_type);

	// process the spawn queue for the current tick
	void process_spawn_queue(const std::shared_ptr<handlers::PathManager>& path_manager, int current_tick);

	// Maintain sorted lists
	void insert_into_sorted_lists(const std::shared_ptr<bloons::BaseBloon> &bloon);
	void remove_from_sorted_lists(const std::shared_ptr<bloons::BaseBloon> &bloon);

public:
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

// base
public:
	BloonManager(const BloonManager&) = delete;
	BloonManager(BloonManager&&) = delete;
	BloonManager& operator=(const BloonManager&) = delete;
	BloonManager& operator=(BloonManager&&) = delete;
	~BloonManager() override;
};

}

#endif