#ifndef MAP_BACKGROUND_HPP
#define MAP_BACKGROUND_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"

#include <vector>
#include <cstring>

namespace map {

class MapBackground {
public:
	MapBackground(float z_index=0);
	
	MapBackground(const MapBackground&) = delete;

	MapBackground(MapBackground&&) = delete;

	MapBackground& operator=(const MapBackground&) = delete;

	MapBackground& operator=(MapBackground&&) = delete;

	virtual ~MapBackground() = default;

	void set_layers(std::vector<std::string> layers);
	
	void add_layer(std::string image_path);
	
	std::vector<std::shared_ptr<Util::GameObject>> get_layers() const {return m_layers;};
protected:
	void recalculate_zIndex();
protected:
	std::vector<std::shared_ptr<Util::GameObject>> m_layers = {};
	
	int m_z_index;
};

}

#endif
