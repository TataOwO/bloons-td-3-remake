#ifndef BLOON_HPP
#define BLOON_HPP

#include "bloons/BaseBloon.hpp"

#include "hitboxes/CircularHitbox.hpp"

#include <string>

namespace bloons {

class Bloon final : public bloons::BaseBloon {
public:
	Bloon(std::shared_ptr<map::route::Route> start_route, bloons::BLOON_TYPE type);
	
    Bloon(const Bloon&) = delete;

    Bloon(Bloon&&) = delete;

    Bloon& operator=(const Bloon&) = delete;

    Bloon& operator=(Bloon&&) = delete;

	~Bloon() override = default;

	void update() override;
	
	void TAKE_DAMAGE(int damage) override; // TODO: remove this
	
	bool has_hp_left() const {return m_hp>0;}
private:
	std::string m_image_path;
	
	void set_bloon_type(bloons::BLOON_TYPE type);
	
	void m_take_damage(int damage) override;
};

}

#endif
