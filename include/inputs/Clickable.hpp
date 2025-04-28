#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP

#include "hitboxes/I_BaseHitbox.hpp"

#include <functional>
#include <memory>
#include <iostream>

namespace inputs {

class Clickable {
public:
	Clickable() = default;
public:
	// returns true when the given object gives a delete signal
	[[nodiscard]] bool shall_be_removed() const {
		return removal_func
			&& removal_func();
	}

	// calls on_click() if clicked, returns true if success
	bool process_click(const glm::vec2 click_pos) const {
		return // evaluate
			(on_click
			&& m_hitbox->contains_point(click_pos)
			&& on_click())
			// debug
			|| ((std::cout << "click processed!" << std::endl) && false);
	}

	// function setter
	void set_removal(const std::function<bool()> &func) {removal_func = func;}
	void set_on_click(const std::function<bool()> &func) {on_click = func;}
	void set_hitbox(const std::shared_ptr<hitboxes::I_BaseHitbox> &hb) {m_hitbox=hb;}
	
	// z index, higher ones will be selected first
	void set_z_index(const float& zi) {z_index = zi;}
	float get_z_index() const {return z_index;}
private:
	// takes function from object
	std::function<bool()> on_click;

	// takes function from object too
	std::function<bool()> removal_func;

	std::shared_ptr<hitboxes::I_BaseHitbox> m_hitbox;

	float z_index = 0;
// base
public:
	Clickable(const Clickable&) = delete;

	Clickable(Clickable&&) = delete;

	Clickable& operator=(const Clickable&) = delete;

	Clickable& operator=(Clickable&&) = delete;

	virtual ~Clickable() = default;
};

}

#endif
