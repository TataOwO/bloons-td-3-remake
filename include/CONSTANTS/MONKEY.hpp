#ifndef MONKEY_CONSTANTS_HPP
#define MONKEY_CONSTANTS_HPP

#include <string_view>

namespace CONSTANTS::MONKEY {
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
}

#endif