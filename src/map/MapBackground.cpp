#include "map/MapBackground.hpp"

#include "Util/Image.hpp"

namespace map {

MapBackground::MapBackground(float z_index) {
	m_z_index = z_index;
}

void MapBackground::set_layers(const std::vector<std::string>& layers) {
	m_layers = {};
	
	for (std::string image_name: layers) {
		add_layer(image_name);
	}
	
	recalculate_zIndex();
}

void MapBackground::add_layer(std::string image_path){
	std::shared_ptr<Util::GameObject> obj = std::make_shared<Util::GameObject>();
	
	obj->SetDrawable(std::make_shared<Util::Image>(image_path));
	obj->SetVisible(true);
	obj->m_Transform.translation = {-120, 0};
	
	m_layers.push_back(obj);
	
	recalculate_zIndex();
}

void MapBackground::recalculate_zIndex() const {
	int total_layers = m_layers.size();
	
	for (int i=0; i<total_layers; ++i) {
		std::shared_ptr<Util::GameObject> layer = m_layers[i];
		
		layer->SetZIndex(m_z_index + (1.0*i/total_layers));
	}
}

}
