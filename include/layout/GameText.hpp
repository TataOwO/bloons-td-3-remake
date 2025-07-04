#ifndef GAME_TEXT_HPP
#define GAME_TEXT_HPP

#include "Util/GameObject.hpp"

namespace Util {class Text;}

namespace layout {

class GameText final : public Util::GameObject {
public:
	GameText(std::string prefix, const int &size);

	void update();

	int get_value() const {return m_value;};
	void set_value(const int& v);
	void add_value(const int& v);
	void sub_value(const int& v);
	
	// activates when an illegal action is called
	void set_blink_red();
private:
	int m_value = 0;
	bool m_is_changed = false;
	
	std::shared_ptr<Util::Text> m_text_obj;
	
	std::string m_prefix;
	
	int m_tick = 0;
	bool is_flashing = false;

// base
public:
	GameText(const GameText&) = delete;

	GameText(GameText&&) = delete;

	GameText& operator=(const GameText&) = delete;

	GameText& operator=(GameText&&) = delete;

	~GameText() override;
};

}

#endif
