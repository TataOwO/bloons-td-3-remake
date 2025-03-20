#ifndef BASE_MONKEY_HPP
#define BASE_MONKEY_HPP

#include <string>
#include <cmath>

#include "Util/GameObject.hpp"

#include "map/route/Route.hpp"

namespace monkeys {

class BaseMonkey : public Util::GameObject {
public:
	BaseMonkey(glm::vec2 position);

	BaseMonkey(const BaseMonkey&) = delete;

	BaseMonkey(BaseMonkey&&) = delete;

	BaseMonkey& operator=(const BaseMonkey&) = delete;

	BaseMonkey& operator=(BaseMonkey&&) = delete;

	bool is_collided_with_route(std::shared_ptr<map::route::Route>) const;

	bool is_collided_with_monkey(std::shared_ptr<BaseMonkey>) const;

	int get_radius() const;

	glm::vec2 get_position() const;

	void face_towards(glm::vec2 position); // TODO: change this to protected

protected:

protected:
	std::string m_image_path;

	// will be used for route
	glm::vec2 m_position;
	int m_radius = 0;

	// for bloons
	glm::vec2 m_face_position;
};

class I_MonkeyAttacker {
public:
	virtual void update_attack_interval();
	virtual void attack();

	virtual bool can_attack();
private:
	glm::vec2 m_projectile_spawn_position;

	int m_attack_interval = 0;
	int m_attack_cooldown = 0;
};

}

#endif