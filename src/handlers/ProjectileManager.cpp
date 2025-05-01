#include "handlers/ProjectileManager.hpp"

#include "bloons/BaseBloon.hpp"
#include "projectiles/BaseProjectile.hpp"

#include "Util/Renderer.hpp"

namespace handlers {

ProjectileManager::ProjectileManager(const std::shared_ptr<Util::Renderer> &render_manager) : m_render_manager(render_manager) {
}

void ProjectileManager::add_new_projectiles(const std::vector<std::shared_ptr<projectiles::BaseProjectile>>& projectile_vec) {
	m_all_projectiles.insert(m_all_projectiles.end(), projectile_vec.begin(), projectile_vec.end());
}

void ProjectileManager::update(const std::vector<std::shared_ptr<bloons::BaseBloon>>& bloon_vec) {
	for (auto& projectile: m_all_projectiles) {
		projectile->update();
		
		for (auto& bloon: bloon_vec) {
			if (!bloon->has_hp_left()) continue; // skips if the bloon should no longer exist
			
			if (projectile->is_collided_with(bloon)) {
				projectile->deal_damage(bloon);
			}
			
			if (projectile->is_dead()) {
				m_render_manager->RemoveChild(projectile);
				m_removal_queue.push_back(projectile);
			}
		}
	}
	
	process_removal();
}

void ProjectileManager::process_removal() {
	for (auto& projectile: m_removal_queue) {
		m_render_manager->RemoveChild(projectile);

		auto it = std::find(m_all_projectiles.begin(), m_all_projectiles.end(), projectile);

		if (it != m_all_projectiles.end()) m_all_projectiles.erase(it);
	}

	m_removal_queue.clear();
}

}
