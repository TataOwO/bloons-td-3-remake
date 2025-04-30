#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP

namespace hitboxes {
    class I_BaseHitbox;
}

namespace inputs {

class Clickable {
public:
	Clickable();
public:
	// returns true when the given object gives a delete signal
	[[nodiscard]] bool shall_be_removed() const;

	// calls on_click() if clicked, returns true if success
	bool process_click(const glm::vec2 click_pos) const;

	// function setter
	void set_removal(const auto& func);
	void set_on_click(const auto& func);
	
	// hitbox setter
	void set_hitbox(const std::shared_ptr<hitboxes::I_BaseHitbox> &hb);
	
	// z index, higher ones will be selected first
	void set_z_index(const float& zi) {z_index = zi;}
	float get_z_index() const {return z_index;}
private:
	// PIMPL IMPLEMENTATION
	class Impl;
	std::unique_ptr<Impl> pImpl;
	
	float z_index = 0;
// base
public:
	Clickable(const Clickable&) = delete;

	Clickable(Clickable&&) = delete;

	Clickable& operator=(const Clickable&) = delete;

	Clickable& operator=(Clickable&&) = delete;

	virtual ~Clickable() = default;
};

}

#endif
