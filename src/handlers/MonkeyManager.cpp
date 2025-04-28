#include "handlers/MonkeyManager.hpp"

#include "Constants.hpp"
#include "layout/GameText.hpp"

namespace handlers {

MonkeyManager::MonkeyManager(const std::shared_ptr<Util::Renderer> &render_manager)
    : m_render_manager(render_manager) {
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

bool MonkeyManager::place_dart_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money) {
	int money_cost = CONSTANTS::MONKEY_CONSTANTS::DART.COST;

    // Check if we have enough money
    if (money_cost > money->get_value()) {
        return false;
    }
    
    // Create the new monkey
    auto new_monkey = std::make_shared<monkeys::DartMonkey>(position);
    
    // Add to our collections
    m_all_monkeys.push_back(new_monkey);
    m_all_monkey_attackers.push_back(new_monkey);
    m_dart_monkeys.push_back(new_monkey);
    
    // Add to renderer
    m_render_manager->AddChild(new_monkey);
    
    // Deduct cost
    money->sub_value(money_cost);
    
    return true;
}

void MonkeyManager::scan_bloons(const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_first, const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_last, const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_strong) {
    // Let each monkey attacker scan for bloons
    for (auto& attacker : m_all_monkey_attackers) {
        switch (attacker->get_targeting()) {
			case monkeys::TARGETING::FIRST:
				for (const auto& bloon : bloon_vec_first) {
					attacker->scan_bloon(bloon);
					if (attacker->has_target()) break;
				}
			break;
			case monkeys::TARGETING::LAST:
				for (const auto& bloon : bloon_vec_last) {
					attacker->scan_bloon(bloon);
					if (attacker->has_target()) break;
				}
			break;
			case monkeys::TARGETING::STRONG:
				for (const auto& bloon : bloon_vec_strong) {
					attacker->scan_bloon(bloon);
					if (attacker->has_target()) break;
				}
			break;
			case monkeys::TARGETING::CLOSE:
				return;
			default: break;
		}
    }
}

void MonkeyManager::process_attacks() {
    // Process attacks for all monkey attackers
    for (auto& attacker : m_all_monkey_attackers) {
        attacker->attack();
        
        // Check if a new projectile was created
        if (attacker->has_projectile()) {
            auto projectile = attacker->get_spawned_projectile();
			
            m_new_projectiles.push_back(projectile);
            m_render_manager->AddChild(projectile);
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

const std::vector<std::shared_ptr<monkeys::BaseMonkey>>& MonkeyManager::get_all_monkeys() const {
    return m_all_monkeys;
}

}
