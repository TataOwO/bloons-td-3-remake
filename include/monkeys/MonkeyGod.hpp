#ifndef MONKEY_GOD_HPP
#define MONKEY_GOD_HPP

#include "monkeys/BaseMonkey.hpp"
#include "monkeys/I_MonkeyAttacker.hpp"

namespace monkeys {

class MonkeyGod final : public monkeys::BaseMonkey, public monkeys::I_MonkeyAttacker {
public:
	explicit MonkeyGod(glm::vec2 position);

	void scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) override;
	void get_random_target(const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec);

	void reset_target() override;

	std::shared_ptr<bloons::BaseBloon> get_target() override;

	bool has_projectile() override {return !m_spawned_projectile.empty();}

	std::vector<std::shared_ptr<projectiles::BaseProjectile>> get_spawned_projectile() override;

	void attack() override;

	bool can_attack() override;

	CONSTANTS::TYPE::MONKEY get_type() override {return CONSTANTS::TYPE::MONKEY::GOD;}

private: // I monkey attacker
	void update_attack_interval() override;

	void spawn_projectile(glm::vec2 position) override;

	void face_towards(glm::vec2 position) override; // TODO: change this to protected

// base
public:
    MonkeyGod(const MonkeyGod&) = delete;

    MonkeyGod(MonkeyGod&&) = delete;

    MonkeyGod& operator=(const MonkeyGod&) = delete;

    MonkeyGod& operator=(MonkeyGod&&) = delete;

	~MonkeyGod() override;
};

}

#endif
