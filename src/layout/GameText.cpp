#include <utility>

#include "layout/GameText.hpp"

#include "CONSTANTS/OPERATION.hpp"
#include "Util/Text.hpp"

namespace layout {

static const Util::Color RED_COLOR(255, 0, 0);
static const Util::Color WHITE_COLOR(255, 255, 255);

GameText::GameText(std::string prefix, const int& size) : m_prefix(std::move(prefix)) {
	std::string font = std::string(CONSTANTS::OPERATION::FONT_BITSTREAM);
	m_text_obj = std::make_shared<Util::Text>(font, size, "0");
	m_text_obj->SetColor(Util::Color(255,255,255));
	
	m_Drawable = m_text_obj;
}

void GameText::update() {
	// updates visual whenever the number is changed
	if (m_is_changed) {
		std::string text = m_prefix + ": " + std::to_string(m_value);
		m_text_obj->SetText(text);
		m_is_changed = false;
	}
	
	// flashing effect
	if (is_flashing) {
		// red
		if (m_tick == 0 || m_tick == 10) {
			m_text_obj->SetColor(RED_COLOR);
		// white
		} else if (m_tick == 5) {
			m_text_obj->SetColor(WHITE_COLOR);
		// back to white and ends the cycle
		} else if (m_tick == 15) {
			m_text_obj->SetColor(WHITE_COLOR);
			is_flashing = false;
			m_tick = 0;
			return;
		}
		
		m_tick++;
	}
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

void GameText::set_blink_red() {
	// resets flashing effect
	is_flashing = true;
	m_tick = 0;
}

GameText::~GameText() {
	
}

}

