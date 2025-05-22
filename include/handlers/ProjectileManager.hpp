#ifndef PROJECTILE_MANAGER_HPP
#define PROJECTILE_MANAGER_HPP

#include "Util/GameObject.hpp"

namespace bloons {class BaseBloon;}

namespace Util {class Renderer;}
namespace projectiles {class BaseProjectile;}

namespace handlers {

class ProjectileManager final : public Util::GameObject {
public:
	ProjectileManager();
public:
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> get_all_projectiles() {return m_all_projectiles;};

	void add_new_projectiles(const std::vector<std::shared_ptr<projectiles::BaseProjectile>>& projectile_vec);

	void update(const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec);
	
	void clear_all_projectiles();
private:
	void process_removal();
private:
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> m_all_projectiles = {};
	
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> m_removal_queue = {};
// base
public:
    ProjectileManager(const ProjectileManager&) = delete;

    ProjectileManager(ProjectileManager&&) = delete;

    ProjectileManager& operator=(const ProjectileManager&) = delete;

    ProjectileManager& operator=(ProjectileManager&&) = delete;

	~ProjectileManager();

};

}

#endif
