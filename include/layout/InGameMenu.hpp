#ifndef IN_GAME_MENU_HPP
#define IN_GAME_MENU_HPP

#include "Util/GameObject.hpp"

namespace Util {class Renderer;}
namespace layout {class Button;}

namespace layout {

class InGameMenu final : public Util::GameObject {
public:
	InGameMenu();
	
	std::vector<std::shared_ptr<layout::Button>> get_buttons() const {return m_buttons;}
private:
	std::shared_ptr<Util::Renderer> m_render_manager;
	
	std::vector<std::shared_ptr<layout::Button>> m_buttons = {};
// base
public:
	InGameMenu(const InGameMenu&) = delete;

	InGameMenu(InGameMenu&&) = delete;

	InGameMenu& operator=(const InGameMenu&) = delete;

	InGameMenu& operator=(InGameMenu&&) = delete;

	~InGameMenu();
};

}

#endif
