#ifndef ICE_PROJECTILE_HPP
#define ICE_PROJECTILE_HPP

#include "projectiles/BaseProjectile.hpp"

namespace projectiles {

class IceProjectile final : public BaseProjectile {
public:
    IceProjectile(const glm::vec2& position, float rotation);

	void update() override;
	
	void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	CONSTANTS::TYPE::PROJECTILE get_type() const override {return CONSTANTS::TYPE::PROJECTILE::ICE;}
private:
    void m_move() override;

// base
public:
	IceProjectile(const IceProjectile&) = delete;

	IceProjectile(IceProjectile&&) = delete;

	IceProjectile& operator=(const IceProjectile&) = delete;

	IceProjectile& operator=(IceProjectile&&) = delete;

	~IceProjectile() override;
};

} // namespace projectiles

#endif