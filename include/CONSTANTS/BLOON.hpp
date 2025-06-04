#ifndef BLOON_CONSTANTS_HPP
#define BLOON_CONSTANTS_HPP

#include <string_view>

namespace CONSTANTS::BLOON {
	constexpr float BLOON_DRIFT_OFFSET = 10;
	
	// BASE BLOON
	typedef struct BLOON {
		int HP;
		float RADIUS;
		std::string_view IMAGE_PATH;
		float SPEED;
	} Bloon;

	namespace MOAB {
		constexpr int HP = 200;
		constexpr float dimension[2] = {210,130};
		constexpr std::string_view IMAGE_PATH = RESOURCE_DIR"/images/bloons/btd6_MOAB.png";
		constexpr float SPEED = 2.4;
	}

	constexpr Bloon RED {
		1,
		23,
		RESOURCE_DIR"/images/bloons/red_bloon.png",
		3.2
	};

	constexpr Bloon BLUE {
		2,
		25,
		RESOURCE_DIR"/images/bloons/blue_bloon.png",
		4
	};

	constexpr Bloon GREEN {
		3,
		26,
		RESOURCE_DIR"/images/bloons/green_bloon.png",
		4.8
	};

	constexpr Bloon YELLOW {
		4,
		27,
		RESOURCE_DIR"/images/bloons/yellow_bloon.png",
		6.4
	};

	constexpr Bloon WHITE {
		5,
		17,
		RESOURCE_DIR"/images/bloons/white_bloon.png",
		8
	};

	constexpr Bloon BLACK {
		5,
		17,
		RESOURCE_DIR"/images/bloons/black_bloon.png",
		8
	};

	constexpr Bloon LEAD {
		5,
		25,
		RESOURCE_DIR"/images/bloons/lead_bloon.png",
		8
	};

	constexpr Bloon RAINBOW {
		1,
		27,
		RESOURCE_DIR"/images/bloons/rainbow_bloon.png",
		10
	};

	constexpr Bloon CERAMIC {
		9,
		28,
		RESOURCE_DIR"/images/bloons/ceramic_bloon.png",
		9.2
	};
}

#endif