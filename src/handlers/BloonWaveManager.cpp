#include "handlers/BloonWaveManager.hpp"

#include "CONSTANTS/WAVE_DATA.hpp"
#include "CONSTANTS/TYPE.hpp"
#include <algorithm>
#include <iostream>

namespace handlers {

BloonWaveManager::BloonWaveManager()
	: current_tick(0)
	, current_wave_index(-1)
	, should_spawn_new_wave(false)
	, wave_state(CONSTANTS::TYPE::WAVE_STATE::WAITING_FOR_START)
{
}

void BloonWaveManager::update(const std::shared_ptr<handlers::BloonManager>& bloon_manager) {
	if (!bloon_manager) return;

	++current_tick;

	switch (wave_state) {
		case CONSTANTS::TYPE::WAVE_STATE::WAITING_FOR_START:
			handle_waiting_for_start(bloon_manager);
			break;

		case CONSTANTS::TYPE::WAVE_STATE::SPAWNING:
			handle_spawning(bloon_manager);
			break;

		case CONSTANTS::TYPE::WAVE_STATE::WAITING_FOR_COMPLETION:
			handle_waiting_for_completion(bloon_manager);
			break;
	}
}

void BloonWaveManager::handle_waiting_for_start(const std::shared_ptr<handlers::BloonManager>& bloon_manager) {
	// if it should start a new wave
	if (should_spawn_new_wave && bloon_manager->is_completely_empty()) {
		start_new_wave();
	}
}

void BloonWaveManager::handle_spawning(const std::shared_ptr<handlers::BloonManager>& bloon_manager) {
    const auto& current_wave_data = CONSTANTS::WAVES::WAVE_DATA.at(current_wave_index);
    
    // schedule all bloons with delays
    for (int i = 0; i < static_cast<int>(current_wave_data.size()); ++i) {
        CONSTANTS::TYPE::BLOON bloon_type = current_wave_data.at(i);
        int delay_ticks = i * SPAWN_INTERVAL_TICKS;
		int bloon_spawn_tick = delay_ticks + current_tick;
        
        bloon_manager->schedule_bloon_spawn(bloon_type, bloon_spawn_tick);
    }
	
	wave_state = CONSTANTS::TYPE::WAVE_STATE::WAITING_FOR_COMPLETION;
}

void BloonWaveManager::handle_waiting_for_completion(const std::shared_ptr<handlers::BloonManager>& bloon_manager) {
	// Wave is complete when all bloons are cleared
	if (bloon_manager->is_completely_empty()) {
		wave_state = CONSTANTS::TYPE::WAVE_STATE::WAITING_FOR_START;
	}
}

void BloonWaveManager::start_new_wave() {
    ++current_wave_index;

    // Check if we have more waves available
    if (current_wave_index >= static_cast<int>(CONSTANTS::WAVES::WAVE_DATA.size())) {
        // No more waves available, stay in waiting state
        --current_wave_index;
        should_spawn_new_wave = false;
        return;
    }

    std::cout << "new wave: " << current_wave_index << std::endl;

    // Transition directly to spawning state
    wave_state = CONSTANTS::TYPE::WAVE_STATE::SPAWNING;
    should_spawn_new_wave = false;
}

int BloonWaveManager::get_current_wave_number() const {
	return current_wave_index + 1; // 1-indexed
}

int BloonWaveManager::get_total_waves() const {
	return static_cast<int>(CONSTANTS::WAVES::WAVE_DATA.size());
}

bool BloonWaveManager::is_all_waves_completed() const {
	return current_wave_index >= static_cast<int>(CONSTANTS::WAVES::WAVE_DATA.size()) - 1
		   && wave_state == CONSTANTS::TYPE::WAVE_STATE::WAITING_FOR_START;
}

bool BloonWaveManager::is_wave_in_progress() const {
	return wave_state == CONSTANTS::TYPE::WAVE_STATE::SPAWNING || wave_state == CONSTANTS::TYPE::WAVE_STATE::WAITING_FOR_COMPLETION;
}

void BloonWaveManager::reset() {
    current_tick = 0;
    current_wave_index = -1;
    should_spawn_new_wave = false;
    wave_state = CONSTANTS::TYPE::WAVE_STATE::WAITING_FOR_START;
}

void BloonWaveManager::_CHEAT_CODE_ADD_ROUND() {
	++current_wave_index;
}

BloonWaveManager::~BloonWaveManager() {

}

}