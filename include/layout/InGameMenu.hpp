#ifndef IN_GAME_MENU_HPP
#define IN_GAME_MENU_HPP

#include "pch.hpp"

#include "Util/Renderer.hpp"

namespace layout {

class InGameMenu {
public:
	InGameMenu(std::shared_ptr<Util::Renderer> render_manager) : m_render_manager(render_manager) {};
private:
	
	std::shared_ptr<Util::Renderer> m_render_manager;
// base
public:
	BaseBloon(const BaseBloon&) = delete;

	BaseBloon(BaseBloon&&) = delete;

	BaseBloon& operator=(const BaseBloon&) = delete;

	BaseBloon& operator=(BaseBloon&&) = delete;

	virtual ~BaseBloon() override = default;
}

}

#endif
