#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Util/GameObject.hpp"
#include "inputs/Clickable.hpp"

namespace Core {class Drawable;}

namespace layout {

enum class BUTTON_STATE {
	INACTIVE,
	HOVER,
	CLICK
};

class Button final : public Util::GameObject, public inputs::Clickable {
public:
	Button() : Util::GameObject(), inputs::Clickable() {};
	
	bool update(const glm::vec2&, const bool&);
	
	void enable() override;
	void disable() override;
	
	BUTTON_STATE get_button_state() const {return m_state;};
	
	void set_drawable(const std::shared_ptr<Core::Drawable>&);
	void set_hover_drawable(const std::shared_ptr<Core::Drawable>&);
private:
	std::shared_ptr<Core::Drawable> m_normal_drawable;
	std::shared_ptr<Core::Drawable> m_hover_drawable;
	
	BUTTON_STATE m_state = BUTTON_STATE::INACTIVE;
// base
public:
	Button(const Button&) = delete;

	Button(Button&&) = delete;

	Button& operator=(const Button&) = delete;

	Button& operator=(Button&&) = delete;

	~Button() override;
};

}

#endif
