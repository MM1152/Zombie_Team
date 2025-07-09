#pragma once
#include "TextGo.h"
class Wave : public TextGo
{
protected:
	sf::Text zombieCount;
	Origins originZombieCount;
public:
	Wave(const std::string& fontId = "", const std::string& name = "");
	~Wave() override = default;

	void SetZombieCount(int count);
	void SetWaveString(int wave);
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
	void SetPosition(const sf::Vector2f& pos) override;
};

