#ifndef SUPER_PROJECTILE_HPP
#define SUPER_PROJECTILE_HPP

#include "projectiles/BaseProjectile.hpp"

namespace projectiles {

class SuperProjectile final : public BaseProjectile {
public:
    SuperProjectile(const glm::vec2& position, float rotation);

	void update() override;
	
	void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	PROJECTILE_TYPE get_type() const override {return PROJECTILE_TYPE::SUPER;}
private:
    void m_move() override;

// base
public:
	SuperProjectile(const SuperProjectile&) = delete;

	SuperProjectile(SuperProjectile&&) = delete;

	SuperProjectile& operator=(const SuperProjectile&) = delete;

	SuperProjectile& operator=(SuperProjectile&&) = delete;

	~SuperProjectile() override;
};

} // namespace projectiles

#endif