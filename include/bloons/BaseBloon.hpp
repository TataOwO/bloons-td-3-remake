#ifndef BASE_BLOON_HPP
#define BASE_BLOON_HPP

#include "pch.hpp" // IWYU pragma: export

#include "map/route/Route.hpp"

#include "hitboxes/I_BaseHitbox.hpp"

namespace bloons {

enum BLOON_TYPE {
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
protected:
	explicit BaseBloon(std::shared_ptr<map::route::Route> start_route);

public:
    BaseBloon(const BaseBloon&) = delete;

    BaseBloon(BaseBloon&&) = delete;

    BaseBloon& operator=(const BaseBloon&) = delete;

    BaseBloon& operator=(BaseBloon&&) = delete;

	virtual ~BaseBloon() = default;

	virtual void update() = 0;

	virtual void TAKE_DAMAGE(int damage) = 0; // TODO: remove this

	bool is_at_end();

	int get_hp();

	glm::vec2 get_pos();

	int get_length_to_exit();
	
	std::shared_ptr<hitboxes::I_BaseHitbox> get_hitbox() {return m_hitbox;}
protected:
	std::shared_ptr<map::route::Route> m_current_route;

	BLOON_TYPE m_type = RED;

	double m_speed = 0;

	int m_hp = 0;

	std::shared_ptr<hitboxes::I_BaseHitbox> m_hitbox;
protected:
	void m_move();

	virtual void m_take_damage(int damage) = 0;
};

}

#endif
