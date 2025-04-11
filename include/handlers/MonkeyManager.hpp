#ifndef MONKEY_MANAGER_HPP
#define MONKEY_MANAGER_HPP

#include "Util/Renderer.hpp"

#include "monkeys/BaseMonkey.hpp"
#include "monkeys/DartMonkey.hpp"

#include "projectiles/BaseProjectile.hpp"
#include "bloons/BaseBloon.hpp"
#include "bloons/Bloon.hpp"

#include "hitboxes/I_BaseHitbox.hpp"
#include "map/route/Route.hpp"

#include "utility/functions.hpp"

namespace handlers {

class MonkeyManager final {
public:
    // Collision detection methods
    bool hitbox_is_collided_with_monkeys(std::shared_ptr<hitboxes::I_BaseHitbox> hitbox);
    bool point_is_collided_with_monkeys(glm::vec2 point);
    
    // Monkey creation and management
    bool place_dart_monkey(glm::vec2 position, int& money);
    
    // Game loop methods
    void scan_bloons(const std::vector<std::shared_ptr<bloons::Bloon>>& bloon_vec);
    void process_attacks();
    
    // Projectile handling
    std::vector<std::shared_ptr<projectiles::BaseProjectile>> get_new_projectiles();
    void clear_new_projectiles();
    
    // Getters
    const std::vector<std::shared_ptr<monkeys::BaseMonkey>>& get_all_monkeys() const;
    
private:
    std::vector<std::shared_ptr<monkeys::BaseMonkey>> m_all_monkeys = {};
    std::vector<std::shared_ptr<monkeys::I_MonkeyAttacker>> m_all_monkey_attackers = {};
    std::vector<std::shared_ptr<monkeys::DartMonkey>> m_dart_monkeys = {};
    
    std::vector<std::shared_ptr<projectiles::BaseProjectile>> m_new_projectiles = {};
    
    std::shared_ptr<Util::Renderer> m_render_manager;

// basic functions
public:
    MonkeyManager(std::shared_ptr<Util::Renderer> render_manager);

    MonkeyManager(const MonkeyManager&) = delete;
    MonkeyManager(MonkeyManager&&) = delete;
    MonkeyManager& operator=(const MonkeyManager&) = delete;
    MonkeyManager& operator=(MonkeyManager&&) = delete;

    ~MonkeyManager() = default;
};

}

#endif