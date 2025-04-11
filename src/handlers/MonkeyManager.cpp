#include "handlers/MonkeyManager.hpp"

namespace handlers {

MonkeyManager::MonkeyManager(std::shared_ptr<Util::Renderer> render_manager)
    : m_render_manager(render_manager) {
}

bool MonkeyManager::hitbox_is_collided_with_monkeys(std::shared_ptr<hitboxes::I_BaseHitbox> hitbox) {
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

bool MonkeyManager::place_dart_monkey(glm::vec2 position, int& money) {
    const int DART_MONKEY_COST = 50;
    
    // Check if we have enough money
    if (money < DART_MONKEY_COST) {
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
    money -= DART_MONKEY_COST;
    
    return true;
}

void MonkeyManager::scan_bloons(const std::vector<std::shared_ptr<bloons::Bloon>>& bloon_vec) {
    // Let each monkey attacker scan for bloons
    for (auto& attacker : m_all_monkey_attackers) {
        for (const auto& bloon : bloon_vec) {
            attacker->scan_bloon(bloon);
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