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

bool Clickable::process_click(glm::vec2 click_pos) const {
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

// reassure function type
void Clickable::set_removal(const void* func_ptr) {
    if (func_ptr) {
        // convert to std::function
        auto& callable = *static_cast<const auto*>(func_ptr);
        pImpl->removal_func = callable;
    }
}

void Clickable::set_on_click(const void* func_ptr) {
    if (func_ptr) {
        // convert to std::function
        auto& callable = *static_cast<const auto*>(func_ptr);
        pImpl->on_click = callable;
    }
}

void Clickable::set_hitbox(const std::shared_ptr<hitboxes::I_BaseHitbox> &hb) const {
	pImpl->hitbox = hb;
}

}
