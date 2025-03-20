#ifndef BASE_BLOON_HPP
#define BASE_BLOON_HPP

#include "pch.hpp" // IWYU pragma: export

#include "map/route/Route.hpp"

namespace bloons {

enum BLOON_TYPE {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	PINK,
	WHITE,
	BLACK,
	LEAD,
	RAINBOW,
	CERAMIC,
	MOAB
};

// https://bloons.fandom.com/wiki/Massive_Ornary_Air_Blimp_(MOAB)
class BaseBloon : public Util::GameObject {
public:
	explicit BaseBloon(std::shared_ptr<map::route::Route> start_route);

    BaseBloon(const BaseBloon&) = delete;

    BaseBloon(BaseBloon&&) = delete;

    BaseBloon& operator=(const BaseBloon&) = delete;

    BaseBloon& operator=(BaseBloon&&) = delete;

	virtual void update() = 0;
	
	bool is_at_end();
	
	int get_hp();
protected:
	std::shared_ptr<map::route::Route> m_current_route;

	BLOON_TYPE m_type = RED;
	
	double m_speed = 0;

	int m_hp = 0;

protected:
	void m_move();
	
	virtual void m_take_damage(int damage) = 0;
};

}

#endif
