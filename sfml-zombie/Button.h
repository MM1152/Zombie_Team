#pragma once
#include "TextGo.h"
class Button : public TextGo
{
protected:
	sf::RectangleShape shape;
	std::string fontId;
	


public:
	Button(const std::string& fontId = "", const std::string& name = "");

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

