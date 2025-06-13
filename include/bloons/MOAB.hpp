#ifndef MOAB_BLOON_HPP
#define MOAB_BLOON_HPP

#include "bloons/BaseBloon.hpp"

namespace bloons {

class MOAB final : public bloons::BaseBloon {
public:
	MOAB(const std::shared_ptr<map::route::Route> &start_route);

	void update() override;

	void handle_take_damage(int damage) override;

	bool has_hp_left() const override {return m_hp>0;}
private:
	std::string m_image_path;

	void m_take_damage(int damage) override;
// base
public:
    MOAB(const MOAB&) = delete;

    MOAB(MOAB&&) = delete;

    MOAB& operator=(const MOAB&) = delete;

    MOAB& operator=(MOAB&&) = delete;

	~MOAB() override;
};

}

#endif
