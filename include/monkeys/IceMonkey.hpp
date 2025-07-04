#ifndef ICE_MONKEY_HPP
#define ICE_MONKEY_HPP

#include "monkeys/BaseMonkey.hpp"
#include "monkeys/I_MonkeyAttacker.hpp"

namespace Util {class Animation;}

namespace monkeys {

class IceMonkey final : public monkeys::BaseMonkey, public monkeys::I_MonkeyAttacker {
public:
	explicit IceMonkey(glm::vec2 position);

	void scan_bloon(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	void reset_target() override;
	
	std::shared_ptr<bloons::BaseBloon> get_target() override;
	
	bool has_projectile() override {return !m_spawned_projectile.empty();}

	std::vector<std::shared_ptr<projectiles::BaseProjectile>> get_spawned_projectile() override;
	
	void attack() override;

	bool can_attack() override;

	CONSTANTS::TYPE::MONKEY get_type() override {return CONSTANTS::TYPE::MONKEY::ICE;}

private: // I monkey attacker
	void update_attack_interval() override;
	
	void spawn_projectile(glm::vec2 position) override;
	
	void face_towards(glm::vec2 position) override; // TODO: change this to protected

private:
	std::shared_ptr<Util::Animation> m_animation;

// base
public:
    IceMonkey(const IceMonkey&) = delete;

    IceMonkey(IceMonkey&&) = delete;

    IceMonkey& operator=(const IceMonkey&) = delete;

    IceMonkey& operator=(IceMonkey&&) = delete;

	~IceMonkey() override;
};

}

#endif
