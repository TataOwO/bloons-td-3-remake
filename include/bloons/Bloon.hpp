#ifndef BLOON_HPP
#define BLOON_HPP

#include "bloons/BaseBloon.hpp"

namespace bloons {

class Bloon final : public bloons::BaseBloon {
public:
	Bloon(const std::shared_ptr<map::route::Route> &start_route, CONSTANTS::TYPE::BLOON type);

	void update() override;
	
	int get_damage() const override;

	void handle_take_damage(int damage) override; // TODO: remove this

	bool has_hp_left() const override {return m_hp>0;}
private:
	std::string m_image_path;

	void set_bloon_type(CONSTANTS::TYPE::BLOON type);

	void m_take_damage(int damage) override;
// base
public:
    Bloon(const Bloon&) = delete;

    Bloon(Bloon&&) = delete;

    Bloon& operator=(const Bloon&) = delete;

    Bloon& operator=(Bloon&&) = delete;

	~Bloon() override;
};

}

#endif
