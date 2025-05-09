#include "monkeys/BaseMonkey.hpp"

#include "Constants.hpp"
#include "hitboxes/CircularHitbox.hpp"
#include "hitboxes/RectangularHitbox.hpp"
#include "map/route/Route.hpp"
#include "Util/Image.hpp"
#include "utility/functions.hpp"

namespace monkeys {
    BaseMonkey::BaseMonkey(glm::vec2 position) {
		m_base_hitbox	= std::make_shared<hitboxes::CircularHitbox>(position, 0);
		m_radius_hitbox	= std::make_shared<hitboxes::CircularHitbox>(position, 0);

		this->SetZIndex(CONSTANTS::Z_INDEX_CONSTANTS::MONKE);
		this->SetVisible(true);
    }

	bool BaseMonkey::is_collided_with_route(const std::shared_ptr<map::route::Route> &route) const {
		const std::shared_ptr<hitboxes::I_BaseHitbox> other = route->get_hitbox();
		return utility::hitboxes_are_collided(other, m_base_hitbox);
	};

	bool BaseMonkey::is_collided_with_monkey(const std::shared_ptr<BaseMonkey> &monke) const {
		auto other = monke->get_hitbox();
		return utility::hitboxes_are_collided(other, m_base_hitbox);
	};

	float BaseMonkey::get_radius() const {
		return m_radius_hitbox->get_radius();
	};

	glm::vec2 BaseMonkey::get_position() const {
		return m_base_hitbox->get_position();
	};

	void BaseMonkey::initialize_with_stat(const CONSTANTS::MONKEY_CONSTANTS::MONKE &stat) {
		m_image_path = std::string(stat.IMAGE_PATH);

		m_base_hitbox	->set_radius(stat.BASE_RADIUS);
		m_radius_hitbox	->set_radius(stat.RANGE_RADIUS);

		m_Transform.scale = {stat.IMAGE_SCALE, stat.IMAGE_SCALE};
	}
}
