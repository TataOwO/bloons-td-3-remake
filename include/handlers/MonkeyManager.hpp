#ifndef MONKEY_MANAGER_HPP
#define MONKEY_MANAGER_HPP

#include "Util/Renderer.hpp"

#include "monkeys/BaseMonkey.hpp"
#include "monkeys/DartMonkey.hpp"

#include "projectiles/BaseProjectile.hpp"

#include "hitboxes/I_BaseHitbox.hpp"

#include "utility/functions.hpp"

namespace handlers {

class MonkeyManager final {
public:
	bool hitbox_is_collided_with_monkeys(std::shared_ptr<hitboxes::I_BaseHitbox> hitbox);

	bool point_is_collided_with_monkeys(glm::vec2 point);
private:
	std::vector<std::shared_ptr<monkeys::BaseMonkey>> m_all_monkeys = {};

	std::vector<std::shared_ptr<monkeys::DartMonkey>> m_dart_monkeys = {};

// basic functions
public:
	MonkeyManager(std::shared_ptr<Util::Renderer> render_manager);

    MonkeyManager(const MonkeyManager&) = delete;

    MonkeyManager(MonkeyManager&&) = delete;

    MonkeyManager& operator=(const MonkeyManager&) = delete;

    MonkeyManager& operator=(MonkeyManager&&) = delete;

	~MonkeyManager() = default;
};

}

#endif
