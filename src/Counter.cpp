#include "Counter.h"

Counter::Counter(const std::string & _prefixText, const sf::Vector2f & position, const sf::Font & font) :
	prefixText(_prefixText),
	number(0)
{
	text.setPosition(position);
	text.setFont(font);
	update();
}
