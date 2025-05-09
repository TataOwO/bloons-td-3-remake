#ifndef GAME_TEXT_HPP
#define GAME_TEXT_HPP

#include "Util/GameObject.hpp"

namespace Util {class Text;}

namespace layout {

class GameText final : public Util::GameObject {
public:
	GameText(const std::string &prefix, const int& size);
	
	void update();

	int get_value() const {return m_value;};
	void set_value(const int& v);
	void add_value(const int& v);
	void sub_value(const int& v);
private:
	int m_value = 0;
	bool m_is_changed = false;
	
	std::shared_ptr<Util::Text> m_text_obj;
	
	std::string m_prefix = "";

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
