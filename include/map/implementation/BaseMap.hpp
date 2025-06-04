#ifndef BASE_MAP_HPP
#define BASE_MAP_HPP

#include "constants/TYPE.hpp"
#include "Util/GameObject.hpp"

namespace hitboxes {class I_BaseHitbox;}
namespace map {class MapBackground;}
namespace handlers {class PathManager;}
namespace inputs {class Clickable;}

namespace map::implementation {

class BaseMap : public Util::GameObject {
protected:
	BaseMap();
public:
	virtual void set_wave(int) = 0;
	virtual void update() = 0;
	virtual CONSTANTS::TYPE::MAP get_map_type() const = 0;
	
	void set_show_route(bool show);
	void toggle_show_route() {set_show_route(!route_is_visible);};
	
	std::shared_ptr<handlers::PathManager> get_path_manager() {return m_path_manager;};

	std::vector<std::shared_ptr<inputs::Clickable>> get_clickables() {return m_clickables;};
	
	std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>> get_obstacles() const {return m_obstacles;};
protected:
	std::shared_ptr<map::MapBackground> m_background;

	// NOT INITIALIZED YET
	std::shared_ptr<handlers::PathManager> m_path_manager;

	std::vector<std::shared_ptr<inputs::Clickable>> m_clickables = {};
	
	std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>> m_obstacles;
	
	int m_current_wave = 1;
private:
	bool route_is_visible = false;

// base
public:
	BaseMap(const BaseMap&) = delete;

	BaseMap(BaseMap&&) = delete;

	BaseMap& operator=(const BaseMap&) = delete;

	BaseMap& operator=(BaseMap&&) = delete;

	~BaseMap() override;
};

}

#endif
