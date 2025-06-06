#ifndef BLOON_WAVE_MANAGER_HPP
#define BLOON_WAVE_MANAGER_HPP

#include "handlers/BloonManager.hpp"

namespace CONSTANTS::TYPE {enum class WAVE_STATE;};

namespace handlers {

class BloonWaveManager { // not a GameObject
public:
	BloonWaveManager();

	void update(const std::shared_ptr<handlers::BloonManager>& bloon_manager);
	void set_spawn_new_wave() { should_spawn_new_wave = true; }

	// utility
	int get_current_wave_number() const;
	int get_total_waves() const;
	bool is_all_waves_completed() const;
	bool is_wave_in_progress() const;
	void reset();
	int get_current_tick() const {return current_tick;};
	void _CHEAT_CODE_ADD_ROUND();
private:
	// handles update based on the state
	void handle_waiting_for_start(const std::shared_ptr<handlers::BloonManager>& bloon_manager);
	void handle_spawning(const std::shared_ptr<handlers::BloonManager>& bloon_manager);
	void handle_waiting_for_completion(const std::shared_ptr<handlers::BloonManager>& bloon_manager);

	// wave management
	void start_new_wave();

	// constants
	static constexpr int SPAWN_INTERVAL_TICKS = 19; // intervals between each bloon spawn

	// state variables
	int current_tick;
	int current_wave_index; // -1 -> no waves, 0 -> first wave
	bool should_spawn_new_wave;

	// Wave spawning state
	CONSTANTS::TYPE::WAVE_STATE wave_state;

// base
public:
	BloonWaveManager(const BloonWaveManager&) = delete;
	BloonWaveManager(BloonWaveManager&&) = delete;
	BloonWaveManager& operator=(const BloonWaveManager&) = delete;
	BloonWaveManager& operator=(BloonWaveManager&&) = delete;
	~BloonWaveManager();
};

}

#endif