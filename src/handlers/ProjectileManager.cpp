#include "handlers/ProjectileManager.hpp"

#include "bloons/BaseBloon.hpp"
#include "hitboxes/I_BaseHitbox.hpp"
#include "projectiles/BaseProjectile.hpp"
#include "projectiles/BombExplosion.hpp"

#include "Util/Renderer.hpp"

namespace handlers {

ProjectileManager::ProjectileManager() {
	
}

void ProjectileManager::add_new_projectiles(const std::vector<std::shared_ptr<projectiles::BaseProjectile>>& projectile_vec) {
	m_all_projectiles.insert(m_all_projectiles.end(), projectile_vec.begin(), projectile_vec.end());
	
	for (auto& p: projectile_vec) {
		AddChild(p);
	}
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
				RemoveChild(projectile);
				m_removal_queue.push_back(projectile);
			}
		}
	}
	
	process_removal();
}

void ProjectileManager::process_removal() {
	std::vector<std::shared_ptr<projectiles::BaseProjectile>> explosions = {};
	
	for (auto& projectile: m_removal_queue) {
		RemoveChild(projectile);

		auto it = std::find(m_all_projectiles.begin(), m_all_projectiles.end(), projectile);

		if (it != m_all_projectiles.end()) m_all_projectiles.erase(it);
		
		if (projectile->get_type() == CONSTANTS::TYPE::PROJECTILE::BOMB && !projectile->has_pierce()) {
			glm::vec2 center = projectile->get_hitbox()->get_position();
			
			explosions.push_back(std::make_shared<projectiles::BombExplosion>(center, 0));
		}
	}

	add_new_projectiles(explosions);

	m_removal_queue.clear();
}

void ProjectileManager::clear_all_projectiles() {
	if (!m_all_projectiles.size()) return;
	
	for (const auto& projectile: m_all_projectiles) {
		RemoveChild(projectile);
	}
	for (const auto& projectile: m_removal_queue) {
		RemoveChild(projectile);
	}
	
	m_all_projectiles.clear();
	m_removal_queue.clear();
}

ProjectileManager::~ProjectileManager() {
	
}

}
