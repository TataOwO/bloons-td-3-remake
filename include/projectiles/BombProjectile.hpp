#ifndef BOMB_PROJECTILE_HPP
#define BOMB_PROJECTILE_HPP

#include "projectiles/BaseProjectile.hpp"

namespace projectiles {

class BombProjectile final : public BaseProjectile {
public:
    BombProjectile(const glm::vec2& position, float rotation);

	void update() override;
	
	void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	PROJECTILE_TYPE get_type() const override {return PROJECTILE_TYPE::BOMB;}
private:
    void m_move() override;

// base
public:
	BombProjectile(const BombProjectile&) = delete;

	BombProjectile(BombProjectile&&) = delete;

	BombProjectile& operator=(const BombProjectile&) = delete;

	BombProjectile& operator=(BombProjectile&&) = delete;

	~BombProjectile() override;
};

} // namespace projectiles

#endif