#ifndef MONKEY_MANAGER_HPP
#define MONKEY_MANAGER_HPP

#include "Util/GameObject.hpp"

namespace Util {class Renderer;}

namespace monkeys {class BaseMonkey;}
namespace monkeys {class I_MonkeyAttacker;}
namespace monkeys {class DartMonkey;}
namespace monkeys {class SuperMonkey;}
namespace monkeys {class IceMonkey;}
namespace monkeys {class BoomerangMonkey;}
namespace monkeys {class BombShooter;}
namespace monkeys {class TackShooter;}
namespace monkeys {class MonkeyGod;}

namespace projectiles {class BaseProjectile;}
namespace bloons {class BaseBloon;}
namespace hitboxes {class I_BaseHitbox;}
namespace layout {class GameText;}

namespace handlers {

class MonkeyManager final : public Util::GameObject {
public:
	MonkeyManager();

	// collision detection
	bool hitbox_is_collided_with_monkeys(const std::shared_ptr<hitboxes::I_BaseHitbox> &hitbox);
	bool point_is_collided_with_monkeys(glm::vec2 point);
	
	// monkey creation
	bool place_dart_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money);
	bool place_super_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money);
	bool place_ice_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money);
	bool place_bomb_shooter(glm::vec2 position, const std::shared_ptr<layout::GameText> &money);
	bool place_tack_shooter(glm::vec2 position, const std::shared_ptr<layout::GameText> &money);
	bool place_boomerang_monkey(glm::vec2 position, const std::shared_ptr<layout::GameText> &money);
	void spawn_god_monkey();
	
	// attack
	void scan_bloons(const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_first, const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_last, const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec_strong);
	void process_attacks();
	
	// projectile
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> get_new_projectiles();
	void clear_new_projectiles();
	
	// monkeys
	std::vector<std::shared_ptr<monkeys::BaseMonkey>> get_all_monkeys() const;
	void clear_all_monkeys();
	
	// sold monkeys
	void process_sold_monkeys(const std::shared_ptr<layout::GameText> &money);
private:
	// monkey removal methods
	void process_removal_queue();
	void remove_from_all_lists(const std::shared_ptr<monkeys::BaseMonkey> &monkey);
private:
	std::vector<std::shared_ptr<monkeys::BaseMonkey>> m_all_monkeys = {};
	std::vector<std::shared_ptr<monkeys::I_MonkeyAttacker>> m_all_monkey_attackers = {};
	std::vector<std::shared_ptr<monkeys::DartMonkey>> m_dart_monkeys = {};
	std::vector<std::shared_ptr<monkeys::SuperMonkey>> m_super_monkeys = {};
	std::vector<std::shared_ptr<monkeys::IceMonkey>> m_ice_monkeys = {};
	std::vector<std::shared_ptr<monkeys::BombShooter>> m_bomb_shooters = {};
	std::vector<std::shared_ptr<monkeys::TackShooter>> m_tack_shooters = {};
	std::vector<std::shared_ptr<monkeys::BoomerangMonkey>> m_boomerang_monkeys = {};
	std::shared_ptr<monkeys::MonkeyGod> m_monkey_god;
	
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> m_new_projectiles = {};
	
	// monkey removal
	std::vector<std::shared_ptr<monkeys::BaseMonkey>> m_removal_queue = {};
	

// basic functions
public:
	MonkeyManager(const MonkeyManager&) = delete;
	MonkeyManager(MonkeyManager&&) = delete;
	MonkeyManager& operator=(const MonkeyManager&) = delete;
	MonkeyManager& operator=(MonkeyManager&&) = delete;

	~MonkeyManager() override;
};

}

#endif