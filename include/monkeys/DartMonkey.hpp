#ifndef DART_MONKEY_HPP
#define DART_MONKEY_HPP

#include "monkeys/BaseMonkey.hpp"

namespace monkeys {

class DartMonkey : public monkeys::BaseMonkey {
public:
	DartMonkey(glm::vec2 position);

    DartMonkey(const DartMonkey&) = delete;

    DartMonkey(DartMonkey&&) = delete;

    DartMonkey& operator=(const DartMonkey&) = delete;

    DartMonkey& operator=(DartMonkey&&) = delete;

private:
};

}

#endif
