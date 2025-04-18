#ifndef BASE_BLOON_HPP
#define BASE_BLOON_HPP

#include <random>
#include <deque>

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

	virtual void handle_take_damage(int damage) = 0;

	std::shared_ptr<map::route::Route> get_current_route() {return m_current_route;};
	bool is_at_end() const {return m_current_route == nullptr;};

	int get_hp() const {return m_hp;};
	virtual bool has_hp_left() const {return m_hp > 0;}

	glm::vec2 get_pos() const {return m_Transform.translation;};

	int get_length_to_exit();

	std::shared_ptr<hitboxes::I_BaseHitbox> get_hitbox() {return m_hitbox;}

	int get_accumulated_money() const {return m_accumulated_money;}
	void reset_accumulated_money() {m_accumulated_money=0;}

	// New methods for path history
	const std::deque<glm::vec2>& get_path_history() const { return m_path_history; }
	void set_max_path_history_size(size_t size) { m_max_path_history_size = size; }
	size_t get_max_path_history_size() const { return m_max_path_history_size; }

	bloons::BLOON_TYPE get_type() const {return m_type;}
	
	bool is_frozen() {return m_frozen_tick!=0;}
	void set_frozen(int t) {m_frozen_tick = (m_frozen_tick<t)? t: m_frozen_tick;}
protected:
	std::shared_ptr<map::route::Route> m_current_route;
	glm::vec2 m_target_point = {};

	BLOON_TYPE m_type = BLOON_TYPE::RED;

	double m_speed = 0;

	int m_hp = 0;

	int m_accumulated_money = 0;

	std::shared_ptr<hitboxes::I_BaseHitbox> m_hitbox;

	// path history
	std::deque<glm::vec2> m_path_history;
	size_t m_max_path_history_size = 20; // Store last 20 positions by default
	
	int m_frozen_tick = 0;

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
}

#endif