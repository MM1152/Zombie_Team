#pragma once
class HitBox
{
protected:
	
	
public:
	
	HitBox();

	sf::RectangleShape rect;
	
	void UpdateTransform(const sf::Transformable& tr, const sf::FloatRect& localBounds);
	void Draw(sf::RenderWindow& window);
};

