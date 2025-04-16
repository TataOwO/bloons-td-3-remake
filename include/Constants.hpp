#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string_view>

namespace CONSTANTS {

struct MonkeyConstants {};

struct ProjectileConstants {};

typedef struct BLOON {
	int hp;
	float radius;
	std::string_view image_path;
	float speed;
} Bloon;

struct BloonConstants {
	struct MOAB {
		int hp = 200;
		float dimension[2] = {210,130};
		std::string_view image_path = RESOURCE_DIR"/images/bloons/btd6_MOAB.png";
		float speed = 2.4;
	};

	inline static constexpr Bloon RED {
		1,
		23,
		RESOURCE_DIR"/images/bloons/red_bloon.png",
		3.2
	};

	inline static constexpr Bloon BLUE {
		2,
		25,
		RESOURCE_DIR"/images/bloons/blue_bloon.png",
		4
	};

	inline static constexpr Bloon GREEN {
		3,
		26,
		RESOURCE_DIR"/images/bloons/green_bloon.png",
		4.8
	};

	inline static constexpr Bloon YELLOW {
		4,
		27,
		RESOURCE_DIR"/images/bloons/yellow_bloon.png",
		6.4
	};

	inline static constexpr Bloon WHITE {
		5,
		17,
		RESOURCE_DIR"/images/bloons/white_bloon.png",
		8
	};

	inline static constexpr Bloon BLACK {
		5,
		17,
		RESOURCE_DIR"/images/bloons/black_bloon.png",
		8
	};

	inline static constexpr Bloon LEAD {
		5,
		25,
		RESOURCE_DIR"/images/bloons/lead_bloon.png",
		8
	};

	inline static constexpr Bloon RAINBOW {
		1,
		27,
		RESOURCE_DIR"/images/bloons/rainbow_bloon.png",
		10
	};

	inline static constexpr Bloon CERAMIC {
		9,
		28,
		RESOURCE_DIR"/images/bloons/ceramic_bloon.png",
		9.2
	};
};
}


#endif

