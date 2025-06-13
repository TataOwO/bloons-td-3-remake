#include "handlers/MonkeyManager.hpp"

#include "Util/Renderer.hpp"

#include "monkeys/DartMonkey.hpp"
#include "monkeys/BombShooter.hpp"
#include "monkeys/IceMonkey.hpp"
#include "monkeys/SuperMonkey.hpp"
#include "monkeys/TackShooter.hpp"
#include "monkeys/BoomerangMonkey.hpp"
#include "monkeys/MonkeyGod.hpp"

#include "projectiles/BaseProjectile.hpp"

#include "bloons/BaseBloon.hpp"
#include "constants/MONKEY.hpp"

#include "hitboxes/CircularHitbox.hpp"
#include "layout/GameText.hpp"


#include "utility/functions.hpp"

namespace handlers {

MonkeyManager::MonkeyManager() {

}

bool MonkeyManager::hitbox_is_collided_with_monkeys(const std::shared_ptr<hitboxes::I_BaseHitbox> &hitbox) {
	for (const auto& monkey : m_all_monkeys) {
		if (utility::hitboxes_are_collided(hitbox, monkey->get_hitbox())) {
			return true;
		}
	}
	return false;
}

bool MonkeyManager::point_is_collided_with_monkeys(glm::vec2 point) {
	for (const auto& monkey : m_all_monkeys) {
		if (monkey->get_hitbox()->contains_point(point)) {
			return true;
		}
	}
	return false;
}

void MonkeyManager::scan_bloons(const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_first, const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_last, const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_strong) {
	// Let each monkey attacker scan for bloons
	for (auto& attacker : m_all_monkey_attackers) {
		switch (attacker->get_targeting()) {
			case CONSTANTS::TYPE::TARGETING::FIRST:
				for (const auto& bloon : bloon_vec_first) {
					attacker->scan_bloon(bloon);
					if (attacker->has_target()) break;
				}
			break;
			case CONSTANTS::TYPE::TARGETING::LAST:
				for (const auto& bloon : bloon_vec_last) {
					attacker->scan_bloon(bloon);
					if (attacker->has_target()) break;
				}
			break;
			case CONSTANTS::TYPE::TARGETING::STRONG:
				for (const auto& bloon : bloon_vec_strong) {
					attacker->scan_bloon(bloon);
					if (attacker->has_target()) break;
				}
			break;
			case CONSTANTS::TYPE::TARGETING::CLOSE:
				return;
			default: break;
		}
	}

	if (!m_monkey_god) return;
	// monkey god handling
	m_monkey_god->get_random_target(bloon_vec_first);
}

void MonkeyManager::process_attacks() {
	// Process attacks for all monkey attackers
	for (auto& attacker : m_all_monkey_attackers) {
		attacker->attack();

		// Check if a new projectile was created
		if (attacker->has_projectile()) {
			auto projectile = attacker->get_spawned_projectile();

			m_new_projectiles.insert(m_new_projectiles.end(), projectile.begin(), projectile.end());
		}

		// Reset target for next scan cycle
		attacker->reset_target();
	}
}

std::vector<std::shared_ptr<projectiles::BaseProjectile>> MonkeyManager::get_new_projectiles() {
	return m_new_projectiles;
}

void MonkeyManager::clear_new_projectiles() {
	m_new_projectiles.clear();
}

std::vector<std::shared_ptr<monkeys::BaseMonkey>> MonkeyManager::get_all_monkeys() const {
	return m_all_monkeys;
}

bool MonkeyManager::place_dart_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money) {
	int money_cost = CONSTANTS::MONKEY::DART.COST;

	// if there isn't enough money
	if (money_cost > money->get_value()) {
		return false;
	}

	auto new_monkey = std::make_shared<monkeys::DartMonkey>(position);
	m_all_monkeys.push_back(new_monkey);
	m_all_monkey_attackers.push_back(new_monkey);
	m_dart_monkeys.push_back(new_monkey);

	// add to renderer
	AddChild(new_monkey);

	money->sub_value(money_cost);

	return true;
}

bool MonkeyManager::place_super_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money) {
	int money_cost = CONSTANTS::MONKEY::SUPER.COST;

	// if there isn't enough money
	if (money_cost > money->get_value()) {
		return false;
	}

	auto new_monkey = std::make_shared<monkeys::SuperMonkey>(position);
	m_all_monkeys.push_back(new_monkey);
	m_all_monkey_attackers.push_back(new_monkey);
	m_super_monkeys.push_back(new_monkey);

	// add to renderer
	AddChild(new_monkey);

	money->sub_value(money_cost);

	return true;
}

bool MonkeyManager::place_ice_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money) {
	int money_cost = CONSTANTS::MONKEY::ICE.COST;

	// if there isn't enough money
	if (money_cost > money->get_value()) {
		return false;
	}

	auto new_monkey = std::make_shared<monkeys::IceMonkey>(position);
	m_all_monkeys.push_back(new_monkey);
	m_all_monkey_attackers.push_back(new_monkey);
	m_ice_monkeys.push_back(new_monkey);

	// add to renderer
	AddChild(new_monkey);

	money->sub_value(money_cost);

	return true;
}

bool MonkeyManager::place_bomb_shooter(glm::vec2 position, const std::shared_ptr<layout::GameText> &money) {
	int money_cost = CONSTANTS::MONKEY::BOMB.COST;

	// if there isn't enough money
	if (money_cost > money->get_value()) {
		return false;
	}

	auto new_monkey = std::make_shared<monkeys::BombShooter>(position);
	m_all_monkeys.push_back(new_monkey);
	m_all_monkey_attackers.push_back(new_monkey);
	m_bomb_shooters.push_back(new_monkey);

	// add to renderer
	AddChild(new_monkey);

	money->sub_value(money_cost);

	return true;
}

bool MonkeyManager::place_tack_shooter(glm::vec2 position, const std::shared_ptr<layout::GameText> &money) {
	int money_cost = CONSTANTS::MONKEY::TACK.COST;

	// if there isn't enough money
	if (money_cost > money->get_value()) {
		return false;
	}

	auto new_monkey = std::make_shared<monkeys::TackShooter>(position);
	m_all_monkeys.push_back(new_monkey);
	m_all_monkey_attackers.push_back(new_monkey);
	m_tack_shooters.push_back(new_monkey);

	// add to renderer
	AddChild(new_monkey);

	money->sub_value(money_cost);

	return true;
}

bool MonkeyManager::place_boomerang_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money) {
	int money_cost = CONSTANTS::MONKEY::BOOMERANG.COST;

	// if there isn't enough money
	if (money_cost > money->get_value()) {
		return false;
	}

	auto new_monkey = std::make_shared<monkeys::BoomerangMonkey>(position);
	m_all_monkeys.push_back(new_monkey);
	m_all_monkey_attackers.push_back(new_monkey);
	m_boomerang_monkeys.push_back(new_monkey);

	// add to renderer
	AddChild(new_monkey);

	money->sub_value(money_cost);

	return true;
}

void MonkeyManager::spawn_god_monkey() {
	if (m_monkey_god) return;

	m_monkey_god = std::make_shared<monkeys::MonkeyGod>(glm::vec2{-120,0});
	AddChild(m_monkey_god);
	m_all_monkeys.push_back(m_monkey_god);
	m_all_monkey_attackers.push_back(m_monkey_god);
}

void MonkeyManager::clear_all_monkeys() {
	for (const auto& monke: m_all_monkeys) {
		RemoveChild(monke);
	}

	m_all_monkeys.clear();
	m_all_monkey_attackers.clear();
	m_dart_monkeys.clear();
	m_super_monkeys.clear();
	m_ice_monkeys.clear();
	m_bomb_shooters.clear();
	m_tack_shooters.clear();
	m_boomerang_monkeys.clear();
	m_new_projectiles.clear();
}

void MonkeyManager::process_sold_monkeys(const std::shared_ptr<layout::GameText> &money) {
	// Check all monkeys for sold status and queue them for removal
	for (auto& monkey : m_all_monkeys) {
		if (monkey->shall_be_sold()) {
			// Add sold money back to player
			money->add_value(monkey->get_sold_money());

			// Queue for removal
			m_removal_queue.push_back(monkey);
		}
	}

	// Process the removal queue
	process_removal_queue();
}

void MonkeyManager::process_removal_queue() {
	for (auto& monkey : m_removal_queue) {
		// Remove from renderer
		RemoveChild(monkey);

		// Remove from all monkey lists
		remove_from_all_lists(monkey);
	}

	// Clear the removal queue
	m_removal_queue.clear();
}

void MonkeyManager::remove_from_all_lists(const std::shared_ptr<monkeys::BaseMonkey> &monkey) {
	// Helper lambda to remove from a specific list
	auto remove_from_list = [monkey](auto& list) {
		auto it = std::find(list.begin(), list.end(), monkey);
		if (it != list.end()) {
			list.erase(it);
		}
	};

	// Remove from all monkey lists
	remove_from_list(m_all_monkeys);
	remove_from_list(m_dart_monkeys);
	remove_from_list(m_super_monkeys);
	remove_from_list(m_ice_monkeys);
	remove_from_list(m_bomb_shooters);
	remove_from_list(m_tack_shooters);
	remove_from_list(m_boomerang_monkeys);

	if (monkey->is_monke_attacker()) {
		auto monke_attacker = std::dynamic_pointer_cast<monkeys::I_MonkeyAttacker>(monkey);

		auto it = std::find(m_all_monkey_attackers.begin(), m_all_monkey_attackers.end(), monke_attacker);
		if (it != m_all_monkey_attackers.end()) {
			m_all_monkey_attackers.erase(it);
		}
	}
}

MonkeyManager::~MonkeyManager() {

}

}
