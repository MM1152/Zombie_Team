#pragma once
#include "stdafx.h"
#include "TextGo.h"
#include "Player.h"



class Player;

class TextBullet : public TextGo
{
protected:
	sf::Sprite bulletImg;
	std::string texIds;

	Player* player;
public:
	TextBullet(const std::string& name = "");
	virtual ~TextBullet() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);

	void SetBulletCount(int curCount , int maxCount);
};

