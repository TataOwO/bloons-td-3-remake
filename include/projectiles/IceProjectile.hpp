#ifndef ICE_PROJECTILE_HPP
#define ICE_PROJECTILE_HPP

#include "projectiles/BaseProjectile.hpp"

namespace projectiles {

class IceProjectile final : public BaseProjectile {
public:
    IceProjectile(const glm::vec2& position, float rotation);

	void update() override;
	
	void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	PROJECTILE_TYPE get_type() const override {return PROJECTILE_TYPE::ICE;}
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