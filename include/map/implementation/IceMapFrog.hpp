#ifndef ICE_MAP_FROG_HPP
#define ICE_MAP_FROG_HPP

#include "Util/GameObject.hpp"

namespace Util {class Image;}
namespace hitboxes {class CircularHitbox;}

namespace map::implementation {

class IceMapFrog : public Util::GameObject {
public:
	IceMapFrog();

	void update();

	bool is_frozen() const {return m_current_state== FROG_STATE::ASLEEP;}

private:
	enum class FROG_STATE {
		ASLEEP,
		WAKING_UP,
		CHASE,
		GRABBED,
		STANDING,
		COOLDOWN
	};

	void set_state(const FROG_STATE& state);
	
	int m_tick = 0;
	int m_click_count = 0;  // for ASLEEP state
	float m_speed = 1.0f;   // for CHASE state

	FROG_STATE m_current_state = FROG_STATE::ASLEEP;

	std::shared_ptr<hitboxes::CircularHitbox> m_hitbox;
	
	std::shared_ptr<Util::Image> m_sleeping;
	std::shared_ptr<Util::Image> m_awakened;
	
	static const glm::vec2 REST_POS;
};

}

#endif