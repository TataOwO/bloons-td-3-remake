#ifndef IN_GAME_MENU_HPP
#define IN_GAME_MENU_HPP

#include "Util/Renderer.hpp"
#include "layout/Button.hpp"

namespace Util {class Renderer;}
namespace layout {class button;}

namespace layout {

class InGameMenu {
public:
	InGameMenu(const std::shared_ptr<Util::Renderer> &render_manager);
	
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

	virtual ~InGameMenu() = default;
};

}

#endif
