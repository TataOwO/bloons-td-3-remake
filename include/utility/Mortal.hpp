#ifndef MORTAL_OBJECT_HPP
#define MORTAL_OBJECT_HPP

namespace utility {

class Mortal {
public:
	Mortal() = default;
	
	bool is_mortal_alive() const {return m_mortal_is_alive;}
	void set_mortal_enable() {m_mortal_is_alive = true;}
	void set_mortal_disable() {m_mortal_is_alive = false;}
private:
	bool m_mortal_is_alive = true;
// base
public:
	Mortal(const Mortal&) = delete;

	Mortal(Mortal&&) = delete;

	Mortal& operator=(const Mortal&) = delete;

	Mortal& operator=(Mortal&&) = delete;

	virtual ~Mortal() = default;
}

}

#endif
