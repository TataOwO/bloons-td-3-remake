#ifndef TACK_PROJECTILE_HPP
#define TACK_PROJECTILE_HPP

#include "projectiles/BaseProjectile.hpp"

namespace projectiles {

class TackProjectile final : public BaseProjectile {
public:
    TackProjectile(const glm::vec2& position, float rotation);

	void update() override;
	
	void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	PROJECTILE_TYPE get_type() const override {return PROJECTILE_TYPE::TACK;}
private:
    void m_move() override;

// base
public:
	TackProjectile(const TackProjectile&) = delete;

	TackProjectile(TackProjectile&&) = delete;

	TackProjectile& operator=(const TackProjectile&) = delete;

	TackProjectile& operator=(TackProjectile&&) = delete;

	~TackProjectile() override;
};

} // namespace projectiles

#endif