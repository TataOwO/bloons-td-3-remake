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
		enum class fileType {PNG, GIF} FILE_TYPE;
	} Monke;
	
	constexpr Monke DART {
		.COST = 215,
		.BASE_RADIUS = 30,
		.RANGE_RADIUS = 100,
		.PROJECTILE_SPAWN_X = 11,
		.PROJECTILE_SPAWN_Y = -24,
		.ATTACK_INTERVAL = 36,
		.IMAGE_PATH = RESOURCE_DIR"/images/monke/dart.png",
		.IMAGE_SCALE = 1.5,
		.FILE_TYPE = MONKE::fileType::PNG,
	};
	
	constexpr Monke SUPER {
		.COST = 3400,
		.BASE_RADIUS = 40,
		.RANGE_RADIUS = 140,
		.PROJECTILE_SPAWN_X = 11,
		.PROJECTILE_SPAWN_Y = -24,
		.ATTACK_INTERVAL = 2,
		.IMAGE_PATH = RESOURCE_DIR"/images/monke/super.png",
		.IMAGE_SCALE = 1.5,
		.FILE_TYPE = MONKE::fileType::PNG,
	};
	
	constexpr Monke ICE {
		.COST = 225,
		.BASE_RADIUS = 30,
		.RANGE_RADIUS = 60,
		.PROJECTILE_SPAWN_X = 0,
		.PROJECTILE_SPAWN_Y = 0,
		.ATTACK_INTERVAL = 70,
		.IMAGE_PATH = RESOURCE_DIR"/images/monke/ice.gif",
		.IMAGE_SCALE = 1.5,
		.FILE_TYPE = MONKE::fileType::GIF,
	};
	
	constexpr Monke BOMB {
		.COST = 615,
		.BASE_RADIUS = 30,
		.RANGE_RADIUS = 120,
		.PROJECTILE_SPAWN_X = 20,
		.PROJECTILE_SPAWN_Y = 0,
		.ATTACK_INTERVAL = 40,
		.IMAGE_PATH = RESOURCE_DIR"/images/monke/bomb.gif",
		.IMAGE_SCALE = 1.5,
		.FILE_TYPE = MONKE::fileType::GIF,
	};
	
	constexpr Monke TACK {
		.COST = 305,
		.BASE_RADIUS = 30,
		.RANGE_RADIUS = 70,
		.PROJECTILE_SPAWN_X = 0,
		.PROJECTILE_SPAWN_Y = 0,
		.ATTACK_INTERVAL = 45,
		.IMAGE_PATH = RESOURCE_DIR"/images/monke/tack.png",
		.IMAGE_SCALE = 2.0,
		.FILE_TYPE = MONKE::fileType::PNG,
	};
	
	constexpr Monke BOOMERANG {
		.COST = 440,
		.BASE_RADIUS = 30,
		.RANGE_RADIUS = 130,
		.PROJECTILE_SPAWN_X = 11,
		.PROJECTILE_SPAWN_Y = -24,
		.ATTACK_INTERVAL = 37,
		.IMAGE_PATH = RESOURCE_DIR"/images/monke/boomerang.png",
		.IMAGE_SCALE = 1.5,
		.FILE_TYPE = MONKE::fileType::PNG,
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
		.HP = 1,
		.RADIUS = 23,
		.IMAGE_PATH = RESOURCE_DIR"/images/bloons/red_bloon.png",
		.SPEED = 3.2
	};

	constexpr Bloon BLUE {
		.HP = 2,
		.RADIUS = 25,
		.IMAGE_PATH = RESOURCE_DIR"/images/bloons/blue_bloon.png",
		.SPEED = 4
	};

	constexpr Bloon GREEN {
		.HP = 3,
		.RADIUS = 26,
		.IMAGE_PATH = RESOURCE_DIR"/images/bloons/green_bloon.png",
		.SPEED = 4.8
	};

	constexpr Bloon YELLOW {
		.HP = 4,
		.RADIUS = 27,
		.IMAGE_PATH = RESOURCE_DIR"/images/bloons/yellow_bloon.png",
		.SPEED = 6.4
	};

	constexpr Bloon WHITE {
		.HP = 5,
		.RADIUS = 17,
		.IMAGE_PATH = RESOURCE_DIR"/images/bloons/white_bloon.png",
		.SPEED = 8
	};

	constexpr Bloon BLACK {
		.HP = 5,
		.RADIUS = 17,
		.IMAGE_PATH = RESOURCE_DIR"/images/bloons/black_bloon.png",
		.SPEED = 8
	};

	constexpr Bloon LEAD {
		.HP = 5,
		.RADIUS = 25,
		.IMAGE_PATH = RESOURCE_DIR"/images/bloons/lead_bloon.png",
		.SPEED = 8
	};

	constexpr Bloon RAINBOW {
		.HP = 1,
		.RADIUS = 27,
		.IMAGE_PATH = RESOURCE_DIR"/images/bloons/rainbow_bloon.png",
		.SPEED = 10
	};

	constexpr Bloon CERAMIC {
		.HP = 9,
		.RADIUS = 28,
		.IMAGE_PATH = RESOURCE_DIR"/images/bloons/ceramic_bloon.png",
		.SPEED = 9.2
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
		};
	};
};

}


#endif

