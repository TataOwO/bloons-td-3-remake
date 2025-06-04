#ifndef BOOMERANG_PROJECTILE_HPP
#define BOOMERANG_PROJECTILE_HPP

#include "projectiles/BaseProjectile.hpp"

namespace projectiles {

class BoomerangProjectile final : public BaseProjectile {
public:
    BoomerangProjectile(const glm::vec2& position, float rotation);

	void update() override;
	
	void deal_damage(std::shared_ptr<bloons::BaseBloon> bloon) override;
	
	CONSTANTS::TYPE::PROJECTILE get_type() const override {return CONSTANTS::TYPE::PROJECTILE::BOOMERANG;}
private:
    void m_move() override;

	std::vector<glm::vec2> m_move_direction_vec = {};

	std::vector<glm::vec2> move_direction_reference_vector = {{0, 0}, {8, 12}, {9, 15}, {6, 17}, {5, 18}, {1, 20}, {-6, 19}, {-10, 16}, {-13, 12}, {-17, 7}, {-20, 0}, {-16, -2}, {-17, -5}, {-13, -12}, {-9, -12}, {-3, -15}, {1, -14}, {4, -12}, {6, -13}, {8, -11}, {9, -1}, {11, -22}, {10, -12}, {14, -11}, {16, -6}, {0, 0}};

// base
public:
	BoomerangProjectile(const BoomerangProjectile&) = delete;

	BoomerangProjectile(BoomerangProjectile&&) = delete;

	BoomerangProjectile& operator=(const BoomerangProjectile&) = delete;

	BoomerangProjectile& operator=(BoomerangProjectile&&) = delete;

	~BoomerangProjectile() override;
};

} // namespace projectiles

#endif