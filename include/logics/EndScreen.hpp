#ifndef END_SCREEN_HPP
#define END_SCREEN_HPP

#include "CONSTANTS/TYPE.hpp"
#include "Util/GameObject.hpp"

namespace CONSTANTS::TYPE {enum class END_SCREEN;}
namespace CONSTANTS::TYPE {enum class GAME_STATE;}
namespace CONSTANTS::TYPE {enum class MAP;}
namespace layout {class Button;}

namespace logics {

class EndScreen : public Util::GameObject {
public:
	EndScreen();

	void init(const CONSTANTS::TYPE::END_SCREEN&, const CONSTANTS::TYPE::MAP&);
	void update() const;
	
	CONSTANTS::TYPE::GAME_STATE get_next_game_state() const {return m_next_game_state;};
private:
	CONSTANTS::TYPE::GAME_STATE m_next_game_state = CONSTANTS::TYPE::GAME_STATE::NO_CHANGE;
	
	std::shared_ptr<layout::Button> m_retry_button;
	std::shared_ptr<layout::Button> m_menu_button;
};

}

#endif