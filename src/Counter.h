#pragma once

#include <SFML/Graphics.hpp>

class Counter : public sf::Drawable
{
public:
	Counter(const std::string& _prefixText,
		const sf::Vector2f& position,
		const sf::Font& font);

	Counter operator++(int);
	Counter operator--(int);

	void reset();
	std::string toString() {
		return std::to_string(number);
	}
private:
	int number;

	sf::Text text;
	std::string prefixText;

	void update() {
		text.setString(prefixText + std::to_string(number));
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(text);
	}
};