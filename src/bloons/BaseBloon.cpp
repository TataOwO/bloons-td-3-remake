#include "bloons/BaseBloon.hpp"

#include <random>

#include "Constants.hpp"

#include "Util/Image.hpp"
#include "Core/Drawable.hpp"
#include "map/route/Route.hpp"
#include "hitboxes/I_BaseHitbox.hpp"

namespace bloons {

BaseBloon::BaseBloon(const std::shared_ptr<map::route::Route> &start_route) {
	m_current_route = start_route;

	m_target_point = twist_pos(m_current_route->get_end_point());

	// add starting pos to history
	if (start_route) {
		m_path_history.push_front(start_route->get_start_point());
	}
	
	// random between 3~4
	SetZIndex(get_random_z_index());
};

int BaseBloon::get_length_to_exit() {
	glm::vec2 end_point_diff = {
		m_target_point[0] - m_Transform.translation[0],
		m_target_point[1] - m_Transform.translation[1],
	};

	// if bloon is at the end (aka route doesn't exist anymore)
	if (!m_current_route) glm::length(end_point_diff);

	return glm::length(end_point_diff) + m_current_route->get_length_to_exit();
};

void BaseBloon::m_move() {
	if (is_at_end()) throw std::runtime_error("bloon is at the end");

	// add pos to history
	m_path_history.push_front(m_Transform.translation);
	if (m_path_history.size() > m_max_path_history_size) {
		m_path_history.pop_back();
	}

	glm::vec2 diff = {
		m_target_point[0] - m_Transform.translation[0],
		m_target_point[1] - m_Transform.translation[1]
	};

	float diff_distance = glm::length(diff);

	if (diff_distance < m_speed) {
		m_Transform.translation = m_target_point;
		m_current_route = m_current_route->get_next_route();

		if (!is_at_end()) m_target_point = twist_pos(m_current_route->get_end_point());
	} else {
		m_Transform.translation = {
			m_Transform.translation[0] + diff[0] * m_speed / diff_distance,
			m_Transform.translation[1] + diff[1] * m_speed / diff_distance
		};
	}

	m_hitbox->set_position(m_Transform.translation);
};

// random number generator for bloon pos
inline std::random_device base_bloon_rd;
inline std::mt19937 base_bloon_gen(base_bloon_rd());
inline std::uniform_real_distribution<double> base_bloon_dist(-CONSTANTS::BLOON_CONSTANTS::BLOON_DRIFT_OFFSET, CONSTANTS::BLOON_CONSTANTS::BLOON_DRIFT_OFFSET);
inline std::uniform_real_distribution<float> base_bloon_z_index_dist(CONSTANTS::Z_INDEX_CONSTANTS::BLOON, CONSTANTS::Z_INDEX_CONSTANTS::BLOON+1);

glm::vec2 BaseBloon::twist_pos(glm::vec2 pos) {
	return pos + glm::vec2{base_bloon_dist(base_bloon_gen), base_bloon_dist(base_bloon_gen)};
}

double BaseBloon::get_random_z_index() {
	return base_bloon_z_index_dist(base_bloon_gen);
}

std::array<std::shared_ptr<Core::Drawable>, 10> BaseBloon::bloon_drawable_arr = {};

const std::shared_ptr<Core::Drawable> BaseBloon::get_bloon_drawable(BLOON_TYPE t) {
	static bool initialized = false;
	if (!initialized) {
		bloon_drawable_arr = {
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::RED.IMAGE_PATH    )),
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::BLUE.IMAGE_PATH   )),
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::GREEN.IMAGE_PATH  )),
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::YELLOW.IMAGE_PATH )),
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::WHITE.IMAGE_PATH  )),
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::BLACK.IMAGE_PATH  )),
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::LEAD.IMAGE_PATH   )),
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::RAINBOW.IMAGE_PATH)),
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::CERAMIC.IMAGE_PATH)),
			std::make_shared<Util::Image>(std::string(CONSTANTS::BLOON_CONSTANTS::MOAB::IMAGE_PATH  ))
		};
		
		initialized = true;
	}
	
	int drawable_index = static_cast<int>(t);
	
	return bloon_drawable_arr.at(drawable_index);
}

BaseBloon::~BaseBloon() {
	
}

}