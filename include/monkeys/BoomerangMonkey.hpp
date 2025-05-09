#ifndef BOOMERANG_MONKEY_HPP
#define BOOMERANG_MONKEY_HPP

#include "monkeys/BaseMonkey.hpp"
#include "monkeys/I_MonkeyAttacker.hpp"

namespace monkeys {

class BoomerangMonkey final : public monkeys::BaseMonkey, public monkeys::I_MonkeyAttacker {
public:
	BoomerangMonkey(glm::vec2 position);

	void scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	void reset_target() override;
	
	std::shared_ptr<bloons::BaseBloon> get_target() override;
	
	bool has_projectile() override {return m_spawned_projectile.size();}

	std::vector<std::shared_ptr<projectiles::BaseProjectile>> get_spawned_projectile() override;
	
	void attack() override;

	bool can_attack() override;

private: // I monkey attacker
	void update_attack_interval() override;
	
	void spawn_projectile(glm::vec2 position) override;
	
	void face_towards(glm::vec2 position) override; // TODO: change this to protected

// base
public:
    BoomerangMonkey(const BoomerangMonkey&) = delete;

    BoomerangMonkey(BoomerangMonkey&&) = delete;

    BoomerangMonkey& operator=(const BoomerangMonkey&) = delete;

    BoomerangMonkey& operator=(BoomerangMonkey&&) = delete;

	~BoomerangMonkey() override;
};

}

#endif
