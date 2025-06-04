#ifndef I_MONKEY_ATTACKER_HPP
#define I_MONKEY_ATTACKER_HPP

namespace bloons {class BaseBloon;}
namespace projectiles {class BaseProjectile;}

namespace monkeys {

class I_MonkeyAttacker {
protected:
	I_MonkeyAttacker() = default;
	virtual ~I_MonkeyAttacker() = default;
public:
	virtual void attack() = 0;

	virtual bool can_attack() = 0;

	virtual void scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) = 0;

	virtual void reset_target() = 0;

	virtual std::shared_ptr<bloons::BaseBloon> get_target() = 0;

	virtual bool has_projectile() = 0;

	virtual std::vector<std::shared_ptr<projectiles::BaseProjectile>> get_spawned_projectile() = 0;

	// not virtual as it only checks if target exists
	bool has_target() const {return m_target_bloon!=nullptr;}

	// not virtual since every objects access this the same way
	CONSTANTS::TYPE::TARGETING get_targeting() const {return m_targeting;}
protected:
	virtual void update_attack_interval() = 0;

	virtual void face_towards(glm::vec2 position) = 0;

	virtual void spawn_projectile(glm::vec2 position) = 0;
protected:
	glm::vec2 m_projectile_spawn_position = {};

	int m_attack_interval = 0;
	int m_attack_cooldown = 0;

	std::vector<std::shared_ptr<projectiles::BaseProjectile>> m_spawned_projectile;

	std::shared_ptr<bloons::BaseBloon> m_target_bloon = nullptr;

	CONSTANTS::TYPE::TARGETING m_targeting = CONSTANTS::TYPE::TARGETING::FIRST;
};

}

#endif
