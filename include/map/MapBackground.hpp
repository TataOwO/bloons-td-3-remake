#ifndef MAP_BACKGROUND_HPP
#define MAP_BACKGROUND_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"

#include <vector>

namespace map {

class MapBackground {
public:
	explicit MapBackground();

	void set_layers(const std::vector<std::string>& layers);
	
	void add_layer(std::string image_path);
	
	std::vector<std::shared_ptr<Util::GameObject>> get_layers() const {return m_layers;};
protected:
	void recalculate_zIndex() const;
protected:
	std::vector<std::shared_ptr<Util::GameObject>> m_layers = {};
	
	float m_z_index;

// base
public:
	MapBackground(const MapBackground&) = delete;

	MapBackground(MapBackground&&) = delete;

	MapBackground& operator=(const MapBackground&) = delete;

	MapBackground& operator=(MapBackground&&) = delete;

	virtual ~MapBackground() = default;
};

}

#endif
