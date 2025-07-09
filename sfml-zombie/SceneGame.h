#pragma once
#include "Scene.h"


class Player;
class Button;
class TextGo;
class Zombie;
class TextScore;
class HpBar;
class TextBullet;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	Button* button = nullptr;
	Zombie* zombie;
	TextScore* textScore;
	HpBar* hpbar;
	TextBullet* textBullet;
	
public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

