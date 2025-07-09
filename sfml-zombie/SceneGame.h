#pragma once
#include "Scene.h"


class Player;
class TextGo;
class Zombie;
class TextScore;
class HpBar;
class TextBullet;
class Wave;
class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	Zombie* zombie;
	TextScore* textScore;
	HpBar* hpbar;
	TextBullet* textBullet;
	Wave* wave;

	int waveValue;
public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

