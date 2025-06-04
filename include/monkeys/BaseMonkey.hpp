#ifndef BASE_MONKEY_HPP
#define BASE_MONKEY_HPP

#include "Util/GameObject.hpp"
#include "Constants.hpp"

namespace hitboxes {class CircularHitbox;}
namespace map::route {class Route;}
namespace bloons {class BaseBloon;}
namespace projectiles {class BaseProjectile;}

namespace monkeys {

class BaseMonkey : public Util::GameObject {
public:
	bool is_collided_with_route(const std::shared_ptr<map::route::Route> &route) const;

	bool is_collided_with_monkey(const std::shared_ptr<BaseMonkey> &monke) const;

	float get_radius() const;

	glm::vec2 get_position() const;

	std::shared_ptr<hitboxes::CircularHitbox> get_hitbox() {return m_base_hitbox;}
protected:
	std::string m_image_path;

	// for route collision
	std::shared_ptr<hitboxes::CircularHitbox> m_base_hitbox;

	// for buff/attack radius
	std::shared_ptr<hitboxes::CircularHitbox> m_radius_hitbox;

	// for bloons
	glm::vec2 m_face_position;
	
	void initialize_with_stat(const CONSTANTS::MONKEY::MONKE &);

protected:
	explicit BaseMonkey(glm::vec2 position);

public:
	BaseMonkey(const BaseMonkey&) = delete;

	BaseMonkey(BaseMonkey&&) = delete;

	BaseMonkey& operator=(const BaseMonkey&) = delete;

	BaseMonkey& operator=(BaseMonkey&&) = delete;

	~BaseMonkey() override;
};

}

#endif