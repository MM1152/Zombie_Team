#pragma once
#include "Scene.h"

class TextGo;
class Zombie;
class TextScore;
class HpBar;
class TextBullet;
class SceneDev1 : public Scene
{
protected:
	Zombie* zombie;
	TextScore* textScore;
	HpBar* hpbar;
	TextBullet* textBullet;
public:
	SceneDev1();
	~SceneDev1() override;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

