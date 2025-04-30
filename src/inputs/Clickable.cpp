#include <inputs/Clickable.hpp>

#include "hitboxes/I_BaseHitbox.hpp"

#include <functional>
#include <iostream>


namespace inputs {

class Clickable::Impl {
public:
	Impl() = default;
	~Impl() = default;
	
	std::function<bool()> on_click;
	std::function<bool()> removal_func;
	std::shared_ptr<hitboxes::I_BaseHitbox> hitbox;
};

Clickable::Clickable() : pImpl(std::make_unique<Impl>()) {}

bool Clickable::shall_be_removed() const {
	return pImpl->removal_func && pImpl->removal_func();
}

bool Clickable::process_click(const glm::vec2 click_pos) const {
	return
		// evaluate
		(
			pImpl->on_click &&
			pImpl->hitbox->contains_point(click_pos) &&
			pImpl->on_click()
		)
		||
		// debug
		((std::cout << "click processed!" << std::endl) && false);
}

// implementing function setters using templates
template <typename Func>
void Clickable::set_removal(const Func& func) {
	pImpl->removal_func = func;
}

template <typename Func>
void Clickable::set_on_click(const Func& func) {
	pImpl->on_click = func;
}

template void Clickable::set_removal<std::function<bool()>>(const std::function<bool()>&);
template void Clickable::set_on_click<std::function<bool()>>(const std::function<bool()>&);

void Clickable::set_hitbox(const std::shared_ptr<hitboxes::I_BaseHitbox>& hb) {
	pImpl->hitbox = hb;
}

}
