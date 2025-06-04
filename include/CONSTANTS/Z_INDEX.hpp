#ifndef Z_INDEX_HPP
#define Z_INDEX_HPP

namespace CONSTANTS::Z_INDEX {
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
}

#endif