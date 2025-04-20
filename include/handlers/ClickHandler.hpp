#ifndef CLICK_HANDLER_HPP
#define CLICK_HANDLER_HPP

namespace handlers {

class ClickHandler final {
public:
	
private:
	
// base
public:
	ClickHandler(const ClickHandler&) = delete;

	ClickHandler(ClickHandler&&) = delete;

	ClickHandler& operator=(const ClickHandler&) = delete;

	ClickHandler& operator=(ClickHandler&&) = delete;

	virtual ~ClickHandler() = default;
};

}

#endif
