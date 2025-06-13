#ifndef BASE_MONKEY_HPP
#define BASE_MONKEY_HPP

#include "constants/TYPE.hpp"
#include "Util/GameObject.hpp"

namespace CONSTANTS::MONKEY {
	struct MONKE;
}

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
	
	// is attcker?
	bool is_monke_attacker() const {return is_attacker;};
	
	virtual CONSTANTS::TYPE::MONKEY get_type() = 0;
	
	// sold state
	void set_sold() {is_sold = true;};
	bool shall_be_sold() const {return is_sold;};
	int get_sold_money() const {return sold_money;};
protected:
	std::string m_image_path;

	// for route collision
	std::shared_ptr<hitboxes::CircularHitbox> m_base_hitbox;

	// for buff/attack radius
	std::shared_ptr<hitboxes::CircularHitbox> m_radius_hitbox;

	// for bloons
	glm::vec2 m_face_position;
	
	void initialize_with_stat(const CONSTANTS::MONKEY::MONKE &);

	// attacker?
	bool is_attacker = false;
	
	// sold
	bool is_sold = false;
	float sold_money = 0;

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