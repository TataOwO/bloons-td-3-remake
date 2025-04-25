#include "utility/GameText.hpp"

namespace utility {

GameText::GameText(int v) : m_value(v) {
	m_Drawable = Util::Text(std::to_string(m_value));
}

void GameText::update() {
	if (!m_is_changed) return;
	
	m_Drawable = Util::Text(std::to_string(m_value));
}

void GameText::set_value(const int& v) {
	if (v_value == v) return;
	
	m_value = v;
	m_is_changed = true;
}

void GameText::add_value(const int& v) {
	if (v == 0) return;
	
	m_value += v;
	m_is_changed = true;
}

void GameText::sub_value(const int& v) {
	if (v == 0) return;
	
	m_value -= v;
	m_is_changed = true;
}

}

