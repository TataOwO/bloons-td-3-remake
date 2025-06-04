#ifndef TYPE_CONSTANTS_HPP
#define TYPE_CONSTANTS_HPP

namespace CONSTANTS::TYPE {

enum class BLOON : int {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	WHITE,
	BLACK,
	LEAD,
	RAINBOW,
	CERAMIC,
	MOAB
};

enum class MONKEY {
	DART,
	BOMB,
	BOOMERANG,
	ICE,
	SUPER,
	TACK
};

enum class HITBOX {
    CIRCULAR,
    OVAL,
    RECTANGULAR,
	GROUPED,
};

enum class MAP {
	PEACEFUL,
	ICE,
	SUMMON,
	TELEPORT,
	SECRET,
};

enum class TARGETING {
	FIRST,
	LAST,
	STRONG,
	CLOSE
};

enum class PLACABLE {
	DART,
	BOOMERANG,
	SUPER,
	ICE,
	BOMB,
	TACK,
	SPIKE,
	GLUE,
	PINEAPPLE,
	VILLAGE,
	CATAPULT,
	_NULL,
};

enum class PROJECTILE {
	DART,
	BOMB,
	EXPLOSION,
	BOOMERANG,
	ICE,
	SUPER,
	TACK
};

enum class WAVE_STATE {
	WAITING_FOR_START, // waiting for player to start next wave
	SPAWNING, // should spawn new bloons
	WAITING_FOR_COMPLETION // all bloons spawned, waiting for them to be cleared
};

}

#endif
