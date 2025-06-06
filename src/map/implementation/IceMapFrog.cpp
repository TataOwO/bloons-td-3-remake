#include "map/implementation/IceMapFrog.hpp"

#include "Util/Input.hpp"
#include "hitboxes/CircularHitbox.hpp"
#include "Util/Image.hpp"

#include <iostream>

namespace map::implementation {

// initialize REST_POS
const glm::vec2 IceMapFrog::REST_POS = {150, -270};

IceMapFrog::IceMapFrog() {
	m_sleeping = std::make_shared<Util::Image>(RESOURCE_DIR"/images/maps/ice_map_sleeping_frog.png");
	m_awakened = std::make_shared<Util::Image>(RESOURCE_DIR"/images/maps/ice_map_awaken_frog.png");
	
	m_hitbox = std::make_shared<hitboxes::CircularHitbox>(REST_POS, 60);

	m_Transform.translation = m_hitbox->get_position();
	SetDrawable(m_sleeping);
	SetZIndex(50);
}

void IceMapFrog::update() {
	++m_tick;

	// mouse pos
	auto mouse_ptsd_pos = Util::Input::GetCursorPosition();
	glm::vec2 mouse_pos = {
		 mouse_ptsd_pos.x,
		-mouse_ptsd_pos.y
	};

	// mouse button
	bool left_button = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);

	switch (m_current_state) {
		case FROG_STATE::ASLEEP:
		{
			// 10 clicks
			if (left_button && (true || std::cout << "mouse clicked" << std::endl) && m_hitbox->contains_point(mouse_pos)) {
				std::cout << "frog clicked" << std::endl;
				++m_click_count;
				if (m_click_count >= 10) {
					std::cout << "frog clicked many" << std::endl;
					set_state(FROG_STATE::WAKING_UP);
				}
			}
			break;
		}

		case FROG_STATE::WAKING_UP:
		{
			// wait for 5 seconds
			if (m_tick >= 60) {
				std::cout << "frog moves" << std::endl;
				set_state(FROG_STATE::CHASE);
			}
			break;
		}

		case FROG_STATE::CHASE:
		{
			// SPEED
			m_speed = m_tick * 0.0166666666;

			// if frog hits the cursor
			if (m_hitbox->contains_point(mouse_pos)) {
				std::cout << "frog got cursor" << std::endl;
				set_state(FROG_STATE::GRABBED);
				break;
			}

			// move frog
			glm::vec2 current_pos = m_hitbox->get_position();
			glm::vec2 direction = mouse_pos - current_pos;
			float distance = glm::length(direction);

			if (distance > 0.0f) {
				glm::vec2 movement = (direction / distance) * m_speed;

				// sets it at cursor if we overshoot
				if (glm::length(movement) >= distance) {
					m_hitbox->set_position(mouse_pos);
				} else {
					m_hitbox->set_position(current_pos + movement);
				}
			}
			break;
		}

		case FROG_STATE::GRABBED:
		{
			// continuously sets mouse to frog pos
			glm::vec2 current_pos = m_hitbox->get_position();
			Util::Input::SetCursorPosition(Util::PTSDPosition(current_pos.x, -current_pos.y));

			// slowly moves back to REST_POS
			glm::vec2 direction = REST_POS - current_pos;
			float distance = glm::length(direction);

			if (distance <= 2.0f) {
				std::cout << "frog reached rest" << std::endl;
				m_hitbox->set_position(REST_POS);
				set_state(FROG_STATE::STANDING);
			} else {
				glm::vec2 movement = (direction / distance) * 2.0f;
				m_hitbox->set_position(current_pos + movement);
			}
			break;
		}

		case FROG_STATE::STANDING:
		{
			Util::Input::SetCursorPosition(Util::PTSDPosition(REST_POS.x, -REST_POS.y));

			// waits 5 seconds
			if (m_tick >= 150) {
				std::cout << "frog sleep" << std::endl;
				set_state(FROG_STATE::COOLDOWN);
			}
			break;
		}

		case FROG_STATE::COOLDOWN:
		{
			// waits 3 minutes
			if (m_tick >= 3600) {
				set_state(FROG_STATE::ASLEEP);
			}
			break;
		}
	}

	m_Transform.translation = m_hitbox->get_position();
}

void IceMapFrog::set_state(const FROG_STATE& state) {
	m_current_state = state;
	m_tick = 0;

	// reset variables for states
	if (state == FROG_STATE::ASLEEP) {
		m_click_count = 0;
		SetDrawable(m_sleeping);
		return; // doesn't set to awakened at the end
	} else if (state == FROG_STATE::COOLDOWN) {
		SetDrawable(m_sleeping);
	} else if (state == FROG_STATE::CHASE) {
		m_speed = 1.0f;
	}

	SetDrawable(m_awakened);
}

}