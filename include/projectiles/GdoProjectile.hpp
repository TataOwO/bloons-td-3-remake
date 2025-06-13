#ifndef GDO_PROJECTILE_HPP
#define GDO_PROJECTILE_HPP

#include "projectiles/BaseProjectile.hpp"

namespace projectiles {

class GdoProjectile final : public BaseProjectile {
public:
    GdoProjectile(const glm::vec2& position, float rotation);

	void update() override;
	
	void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	CONSTANTS::TYPE::PROJECTILE get_type() const override {return CONSTANTS::TYPE::PROJECTILE::SUPER;}
private:
    void m_move() override;

// base
public:
	GdoProjectile(const GdoProjectile&) = delete;

	GdoProjectile(GdoProjectile&&) = delete;

	GdoProjectile& operator=(const GdoProjectile&) = delete;

	GdoProjectile& operator=(GdoProjectile&&) = delete;

	~GdoProjectile() override;
};

} // namespace projectiles

#endif