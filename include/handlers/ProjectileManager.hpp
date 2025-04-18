#ifndef PROJECTILE_MANAGER_HPP
#define PROJECTILE_MANAGER_HPP

#include "projectiles/BaseProjectile.hpp"

#include "Util/Renderer.hpp"

namespace handlers {

class ProjectileManager final {
public:
	ProjectileManager(std::shared_ptr<Util::Renderer> render_manager);
public:
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> get_all_projectiles() {return m_all_projectiles;};

	void add_new_projectiles(const std::vector<std::shared_ptr<projectiles::BaseProjectile>>& projectile_vec);

	void update(const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec);
private:
	void process_removal();
private:
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> m_all_projectiles = {};
	
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> m_removal_queue = {};

	std::shared_ptr<Util::Renderer> m_render_manager;
// base
public:
    ProjectileManager(const ProjectileManager&) = delete;

    ProjectileManager(ProjectileManager&&) = delete;

    ProjectileManager& operator=(const ProjectileManager&) = delete;

    ProjectileManager& operator=(ProjectileManager&&) = delete;

	~ProjectileManager() = default;

};

}

#endif
