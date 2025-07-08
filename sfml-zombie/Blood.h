#pragma once
#include "GameObject.h"
class Blood : public GameObject
{
protected:
	sf::Sprite body;
	sf::String texId;

	sf::Color initColor;
	sf::Color curColor;
public:
	Blood(const std::string& name = "");
	virtual ~Blood() = default;

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

