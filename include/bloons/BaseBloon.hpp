#ifndef BASE_BLOON_HPP
#define BASE_BLOON_HPP

#include <random>

#include "pch.hpp" // IWYU pragma: export

#include "map/route/Route.hpp"

#include "hitboxes/I_BaseHitbox.hpp"

namespace bloons {

enum class BLOON_TYPE {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	WHITE,
	BLACK,
	LEAD,
	RAINBOW,
	CERAMIC,
	MOAB
};

// https://bloons.fandom.com/wiki/Massive_Ornary_Air_Blimp_(MOAB)
class BaseBloon : public Util::GameObject {
// protected constructor to prevent direct use of this class
protected:
	explicit BaseBloon(const std::shared_ptr<map::route::Route> &start_route);
public:
	virtual void update() = 0;

	virtual void TAKE_DAMAGE(int damage) = 0;

	bool is_at_end() const {return m_current_route == nullptr;};

	int get_hp() const {return m_hp;};

	glm::vec2 get_pos() const {return m_Transform.translation;};

	int get_length_to_exit();

	std::shared_ptr<hitboxes::I_BaseHitbox> get_hitbox() {return m_hitbox;}

	int get_accumulated_money() const {return m_accumulated_money;}
	void reset_accumulated_money() {m_accumulated_money=0;}
protected:
	std::shared_ptr<map::route::Route> m_current_route;
	glm::vec2 m_target_point = {};

	BLOON_TYPE m_type = BLOON_TYPE::RED;

	double m_speed = 0;

	int m_hp = 0;

	int m_accumulated_money = 0;

	std::shared_ptr<hitboxes::I_BaseHitbox> m_hitbox;
protected:
	void m_move();

	virtual void m_take_damage(int damage) = 0;
private:
	static glm::vec2 twist_pos(glm::vec2 pos);
// base
public:
    BaseBloon(const BaseBloon&) = delete;

    BaseBloon(BaseBloon&&) = delete;

    BaseBloon& operator=(const BaseBloon&) = delete;

    BaseBloon& operator=(BaseBloon&&) = delete;

	virtual ~BaseBloon() override = default;
};

// random number generator for bloon pos
inline std::random_device base_bloon_rd;
inline std::mt19937 base_bloon_gen(base_bloon_rd());
inline std::uniform_real_distribution<double> base_bloon_dist(-10.0,10.0);
}

#endif
