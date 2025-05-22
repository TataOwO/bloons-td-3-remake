#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string_view>

namespace CONSTANTS {

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
		std::string_view IMAGE_PATH;
		float IMAGE_SCALE;
	} Monke;
	
	constexpr Monke DART {
		215,
		30,
		100,
		11,
		-24,
		36,
		RESOURCE_DIR"/images/monke/dart.png",
		1.5,
	};
	
	constexpr Monke SUPER {
		3400,
		40,
		140,
		11,
		-24,
		2,
		RESOURCE_DIR"/images/monke/super.png",
		1.5,
	};
	
	constexpr Monke ICE {
		225,
		30,
		60,
		0,
		0,
		70,
		RESOURCE_DIR"/images/monke/ice/",
		1.5,
	};
	
	constexpr Monke BOMB {
		615,
		30,
		120,
		20,
		0,
		40,
		RESOURCE_DIR"/images/monke/bomb/",
		1.5,
	};
	
	constexpr Monke TACK {
		305,
		30,
		70,
		0,
		0,
		45,
		RESOURCE_DIR"/images/monke/tack.png",
		1.5,
	};
	
	constexpr Monke BOOMERANG {
		440,
		30,
		130,
		11,
		-24,
		37,
		RESOURCE_DIR"/images/monke/boomerang.png",
		1.5,
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
		30,
		1,
		20.0f
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

	namespace MOAB {
		constexpr int HP = 200;
		constexpr float dimension[2] = {210,130};
		constexpr std::string_view IMAGE_PATH = RESOURCE_DIR"/images/bloons/btd6_MOAB.png";
		constexpr float SPEED = 2.4;
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

namespace HITBOX_CONSTANTS {
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
};

}


#endif

