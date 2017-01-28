#include "Counter.h"

Counter::Counter(const std::string & _prefixText, const sf::Vector2f & position, const sf::Font & font) :
	prefixText(_prefixText),
	number(0)
{
	text.setPosition(position);
	text.setFont(font);
	update();
}

Counter Counter::operator++(int)
{
	Counter copy(*this);
	number++;
	update();
	return copy;
}

Counter Counter::operator--(int)
{
	Counter copy(*this);
	number--;
	update();
	return copy;
}

void Counter::reset()
{
	number = 0;
	update();
}
