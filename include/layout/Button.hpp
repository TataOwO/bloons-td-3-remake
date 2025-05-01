#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Util/GameObject.hpp"
#include "inputs/Clickable.hpp"

namespace layout {

class Button final : public Util::GameObject, public inputs::Clickable {
public:
	Button() : Util::GameObject(), inputs::Clickable() {};
private:
// base
public:
	Button(const Button&) = delete;

	Button(Button&&) = delete;

	Button& operator=(const Button&) = delete;

	Button& operator=(Button&&) = delete;

	virtual ~Button() override = default;
};

}

#endif
