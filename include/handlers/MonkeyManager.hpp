#ifndef MONKEY_MANAGER_HPP
#define MONKEY_MANAGER_HPP

namespace Util {class Renderer;}

namespace monkeys {class BaseMonkey;}
namespace monkeys {class I_MonkeyAttacker;}
namespace monkeys {class DartMonkey;}

namespace projectiles {class BaseProjectile;}
namespace bloons {class BaseBloon;}
namespace hitboxes {class I_BaseHitbox;}
namespace layout {class GameText;}

namespace handlers {

class MonkeyManager final {
public:
    // Collision detection methods
    bool hitbox_is_collided_with_monkeys(const std::shared_ptr<hitboxes::I_BaseHitbox> &hitbox);
    bool point_is_collided_with_monkeys(glm::vec2 point);
    
    // Monkey creation and management
    bool place_dart_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money);
    
    // Game loop methods
    void scan_bloons(const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_first, const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_last, const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_strong);
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
    MonkeyManager(const std::shared_ptr<Util::Renderer> &render_manager);

    MonkeyManager(const MonkeyManager&) = delete;
    MonkeyManager(MonkeyManager&&) = delete;
    MonkeyManager& operator=(const MonkeyManager&) = delete;
    MonkeyManager& operator=(MonkeyManager&&) = delete;

    ~MonkeyManager() = default;
};

}

#endif