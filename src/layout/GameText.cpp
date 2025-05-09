#include "layout/GameText.hpp"

#include "Util/Text.hpp"
#include "Constants.hpp"

namespace layout {

GameText::GameText(const std::string &prefix, const int& size) : m_prefix(prefix) {
	std::string font = std::string(CONSTANTS::OPERATION_CONSTANTS::BITSTREAM);
	m_text_obj = std::make_shared<Util::Text>(font, size, "0");
	m_text_obj->SetColor(Util::Color(255,255,255));
	
	m_Drawable = m_text_obj;
}

void GameText::update() {
	if (!m_is_changed) return;
	
	std::string text = m_prefix + ": " + std::to_string(m_value);
	m_text_obj->SetText(text);
	m_is_changed = false;
}

void GameText::set_value(const int& v) {
	if (m_value == v) return;
	
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

GameText::~GameText() {
	
}

}

