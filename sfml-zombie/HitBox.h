#pragma once
class HitBox
{
protected:
	sf::RectangleShape rect;
	
public:
	
	HitBox();

	void UpdateTransform(const sf::Transformable& tr, const sf::FloatRect& localBounds);
	void Draw(sf::RenderWindow& window);
};

