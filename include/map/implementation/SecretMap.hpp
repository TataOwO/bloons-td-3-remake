#ifndef SECRET_MAP_HPP
#define SECRET_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace map::implementation {

class SecretMap final : public BaseMap {
public:
	SecretMap();

	void set_wave(int) override;
	void update() override;

	CONSTANTS::TYPE::MAP get_map_type() const override {return CONSTANTS::TYPE::MAP::SECRET;}
private:

// base
public:
	SecretMap(const SecretMap&) = delete;

	SecretMap(SecretMap&&) = delete;

	SecretMap& operator=(const SecretMap&) = delete;

	SecretMap& operator=(SecretMap&&) = delete;

	~SecretMap() override;
};

}

#endif
