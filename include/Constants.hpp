#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string_view>

namespace CONSTANTS {

namespace HITBOX_CONSTANTS {
	constexpr int OVAL_SAMPLE_COUNT = 8;
	constexpr int RECTANGLE_SAMPLE_COUNT = 8;
	
	struct COLLISION_CHECK_PRIORITY {
		enum : int {
			CIRCULAR,
			OVAL,
			RECTANGULAR,
		};
	};
};

namespace OPERATION_CONSTANTS {
	constexpr int GAME_HP = 200;
	constexpr int MONEY = 100000;
	constexpr std::string_view BITSTREAM = RESOURCE_DIR"/fonts/VeraMono.ttf";
};

namespace MONKEY_CONSTANTS {
	// BASE MONKE
	typedef struct MONKE {
		int COST;
		int BASE_RADIUS;
		int RANGE_RADIUS;
		int PROJECTILE_SPAWN_X;
		int PROJECTILE_SPAWN_Y;
		int ATTACK_INTERVAL;
	} Monke;
	
	constexpr Monke DART {
		50,
		30,
		100,
		24,
		11,
		30
	};
};

namespace PROJECTILE_CONSTANTS {
	// BASE PROJECTILE
	typedef struct PROJECTILE {
		int DAMAGE;
		int EXTRA_CERAMIC_DAMAGE;
		int SURVIVE_PERIOD;
		int PIERCE;
		float SPEED;
	} Projectile;

	constexpr Projectile DART {
		1,
		0,
		60,
		2,
		30.0f
	};
};

namespace BLOON_CONSTANTS {
	constexpr float BLOON_DRIFT_OFFSET = 10;
	
	// BASE BLOON
	typedef struct BLOON {
		int HP;
		float RADIUS;
		std::string_view IMAGE_PATH;
		float SPEED;
	} Bloon;

	struct MOAB {
		int hp = 200;
		float dimension[2] = {210,130};
		std::string_view image_path = RESOURCE_DIR"/images/bloons/btd6_MOAB.png";
		float speed = 2.4;
	};

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
};

struct Z_INDEX_CONSTANTS {
	// this will automatically allocate numbers for them
	enum : int {
		// in game
		MAP_BACKGROUND,
		MAP_OBJECTS,
		ROUTE,
		BLOON,
		MONKE_RANGE,
		MONKE,
		PROJECTILE,
		IN_GAME_MENU,
		IN_GAME_BUTTONS,
		TEXT,
		ESCAPE_MENU,
		ESCAPE_BUTTON,

		// map selection
		MAP_SELECTOR,
		DIFFICULTY_SELECTOR,
		OTHER_BUTTONS,
		EASTER_EGGS,
	};
};

}


#endif

