#ifndef BLOON_HPP
#define BLOON_HPP

#include "bloons/BaseBloon.hpp"

#include <string>

namespace bloons {

class Bloon final : public bloons::BaseBloon {
public:
	Bloon(std::shared_ptr<map::route::Route> start_route, bloons::BLOON_TYPE type);
	
    Bloon(const Bloon&) = delete;

    Bloon(Bloon&&) = delete;

    Bloon& operator=(const Bloon&) = delete;

    Bloon& operator=(Bloon&&) = delete;

	void update() override;
private:
	std::string m_image_path;
	
	int m_radius;
	
	void m_take_damage(int damage) override;
};

}

#endif
