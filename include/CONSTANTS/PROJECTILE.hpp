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
		22,
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
		40,
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
		10,
		2,
		20.0f
	};

	constexpr Projectile BOOMERANG {
		1,
		1,
		25,
		5,
		0.0f // doesn't matter
	};

	constexpr Projectile DART {
		1,
		0,
		7,
		2,
		20.0f
	};

	constexpr Projectile GDO {
		5,
		6,
		30,
		100,
		50.0f
	};
}

#endif