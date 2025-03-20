#include "monkeys/DartMonkey.hpp"

namespace monkeys {
	DartMonkey::DartMonkey(glm::vec2 position)
	: BaseMonkey(position) {
		m_image_path = RESOURCE_DIR"/images/dart_monkey_1.5.png";
		
		m_Transform.translation = position;
		
		m_radius = 56;
		
		m_Drawable = std::make_shared<Util::Image>(m_image_path);
	};
}