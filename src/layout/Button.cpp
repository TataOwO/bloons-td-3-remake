#include "layout/Button.hpp"

#include "Core/Drawable.hpp"

namespace layout {

bool Button::update(const glm::vec2& pos, const bool& clicked) {
	if (!m_hitbox) return false;
	if (!m_hitbox->contains_point(pos)) {
		SetDrawable(m_normal_drawable);
		return false;
	}
	
	if (!clicked) {
		m_state = BUTTON_STATE::HOVER;
		SetDrawable(m_hover_drawable);
		return false;
	}
	
	// bool clicked = process_click(pos);
	//if (clicked) m_state = BUTTON_STATE::INACTIVE;
	return process_click(pos);
}

void Button::set_drawable(const std::shared_ptr<Core::Drawable>& drawable) {
	m_normal_drawable = drawable;
}

void Button::set_hover_drawable(const std::shared_ptr<Core::Drawable>& drawable) {
	m_hover_drawable = drawable;
}

Button::~Button() {
	
}

}
