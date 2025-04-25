#ifndef GAME_TEXT_HPP
#define GAME_TEXT_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"

namespace utility {

class GameText final : public Util::GameObject {
public:
	GameText(int v);
	
	void update();
	
	void set_value(const int& v);
	void add_value(const int& v);
	void sub_value(const int& v);
private:
	int m_value = 0;
	bool m_is_changed = false;

// base
public:
	GameText(const GameText&) = delete;

	GameText(GameText&&) = delete;

	GameText& operator=(const GameText&) = delete;

	GameText& operator=(GameText&&) = delete;

	~GameText() = default;
}

}

#endif
