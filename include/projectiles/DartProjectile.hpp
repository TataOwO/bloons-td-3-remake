#ifndef DART_PROJECTILE_HPP
#define DART_PROJECTILE_HPP

#include "projectiles/BaseProjectile.hpp"
#include "hitboxes/RectangularHitbox.hpp"

namespace projectiles {

class DartProjectile final : public BaseProjectile {
public:
    DartProjectile(const glm::vec2& position, float rotation);

	DartProjectile(const DartProjectile&) = delete;

	DartProjectile(DartProjectile&&) = delete;

	DartProjectile& operator=(const DartProjectile&) = delete;

	DartProjectile& operator=(DartProjectile&&) = delete;

	~DartProjectile() = default;

	void update() override;
	
	void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) override;
private:
    void m_move() override;
};

} // namespace projectiles

#endif