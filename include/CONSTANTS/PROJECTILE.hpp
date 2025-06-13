#ifndef PROJECTILE_CONSTANTS_HPP
#define PROJECTILE_CONSTANTS_HPP

namespace CONSTANTS::PROJECTILE {
	// BASE PROJECTILE
	typedef struct PROJECTILE {
		int DAMAGE;
		int EXTRA_CERAMIC_DAMAGE;
		int SURVIVE_PERIOD;
		int PIERCE;
		float SPEED;
	} Projectile;

	constexpr Projectile EXPLOSION {
		2,
		1,
		15,
		20,
		0.0f, // doesn't matter
	};

	constexpr Projectile BOMB {
		0,
		0,
		7,
		1,
		20.0f
	};

	constexpr Projectile ICE {
		1,
		0,
		3,
		20,
		0, // doesn't matter
	};

	constexpr Projectile TACK {
		1,
		0,
		4,
		1,
		20.0f
	};

	constexpr Projectile SUPER {
		1,
		1,
		15,
		1,
		20.0f
	};

	constexpr Projectile BOOMERANG {
		1,
		1,
		25,
		3,
		0.0f // doesn't matter
	};

	constexpr Projectile DART {
		1,
		0,
		7,
		1,
		20.0f
	};

	constexpr Projectile GDO {
		5,
		6,
		30,
		100,
		30.0f
	};
}

#endif