#ifndef BOMB_SHOOTER_HPP
#define BOMB_SHOOTER_HPP

#include "monkeys/BaseMonkey.hpp"
#include "monkeys/I_MonkeyAttacker.hpp"

namespace Util {class Animation;}

namespace monkeys {

class BombShooter final : public monkeys::BaseMonkey, public monkeys::I_MonkeyAttacker {
public:
	BombShooter(glm::vec2 position);

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

private:
	std::shared_ptr<Util::Animation> m_animation;

// base
public:
    BombShooter(const BombShooter&) = delete;

    BombShooter(BombShooter&&) = delete;

    BombShooter& operator=(const BombShooter&) = delete;

    BombShooter& operator=(BombShooter&&) = delete;

	~BombShooter() override;
};

}

#endif
