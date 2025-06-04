#ifndef BOMB_EXPLOSION_HPP
#define BOMB_EXPLOSION_HPP

#include "projectiles/BaseProjectile.hpp"

namespace projectiles {

class BombExplosion final : public BaseProjectile {
public:
    BombExplosion(const glm::vec2& position, float rotation);

	void update() override;
	
	void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	CONSTANTS::TYPE::PROJECTILE get_type() const override {return CONSTANTS::TYPE::PROJECTILE::EXPLOSION;}
private:
    void m_move() override;

// base
public:
	BombExplosion(const BombExplosion&) = delete;

	BombExplosion(BombExplosion&&) = delete;

	BombExplosion& operator=(const BombExplosion&) = delete;

	BombExplosion& operator=(BombExplosion&&) = delete;

	~BombExplosion() override;
};

} // namespace projectiles

#endif