#ifndef TACK_SHOOTER_HPP
#define TACK_SHOOTER_HPP

#include "monkeys/BaseMonkey.hpp"
#include "monkeys/I_MonkeyAttacker.hpp"

namespace monkeys {

class TackShooter final : public monkeys::BaseMonkey, public monkeys::I_MonkeyAttacker {
public:
	explicit TackShooter(glm::vec2 position);

	void scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	void reset_target() override;
	
	std::shared_ptr<bloons::BaseBloon> get_target() override;
	
	bool has_projectile() override {return !m_spawned_projectile.empty();}

	std::vector<std::shared_ptr<projectiles::BaseProjectile>> get_spawned_projectile() override;
	
	void attack() override;

	bool can_attack() override;

	static MONKEY_TYPE get_type() {return MONKEY_TYPE::TACK;}

private: // I monkey attacker
	void update_attack_interval() override;
	
	void spawn_projectile(glm::vec2 position) override;
	
	void face_towards(glm::vec2 position) override; // TODO: change this to protected

// base
public:
    TackShooter(const TackShooter&) = delete;

    TackShooter(TackShooter&&) = delete;

    TackShooter& operator=(const TackShooter&) = delete;

    TackShooter& operator=(TackShooter&&) = delete;

	~TackShooter() override;
};

}

#endif
