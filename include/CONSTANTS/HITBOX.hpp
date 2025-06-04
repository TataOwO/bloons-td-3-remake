#ifndef HITBOX_CONSTANTS_HPP
#define HITBOX_CONSTANTS_HPP

namespace CONSTANTS::HITBOX {
	constexpr int OVAL_SAMPLE_COUNT = 8;
	constexpr int RECTANGLE_SAMPLE_COUNT = 8;
	
	struct COLLISION_CHECK_PRIORITY {
		enum : int {
			CIRCULAR,
			OVAL,
			RECTANGULAR,
			GROUP,
		};
	};
}

#endif