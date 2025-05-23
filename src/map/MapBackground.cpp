#include "map/MapBackground.hpp"

#include "Constants.hpp"
#include "Util/Image.hpp"

namespace map {

MapBackground::MapBackground() {
	m_z_index = CONSTANTS::Z_INDEX_CONSTANTS::MAP_BACKGROUND;
}

void MapBackground::set_layers(const std::vector<std::string>& layers) {
	for (auto& obj: GetChildren()) {
		RemoveChild(obj);
	}
	
	for (const std::string& image_name: layers) {
		add_layer(image_name);
	}
	
	recalculate_zIndex();
}

void MapBackground::add_layer(const std::string& image_path){
	auto obj = std::make_shared<Util::GameObject>();
	
	AddChild(obj);
	
	obj->SetDrawable(std::make_shared<Util::Image>(image_path));
	obj->SetVisible(true);
	obj->m_Transform.translation = {-120, 0};
	
	m_layers.push_back(obj);
	
	recalculate_zIndex();
}

void MapBackground::recalculate_zIndex() const {
	auto total_layers = m_layers.size();
	
	for (unsigned int i=0; i<total_layers; ++i) {
		std::shared_ptr<Util::GameObject> layer = m_layers[i];
		
		layer->SetZIndex(m_z_index + (1.0*i/total_layers));
	}
}

MapBackground::~MapBackground() {
	
}

}
