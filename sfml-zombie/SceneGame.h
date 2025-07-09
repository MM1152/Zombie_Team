#pragma once
#include "Scene.h"
#include "Item.h"


class Player;
class TextGo;
class Zombie;
class TextScore;
class HpBar;
class TextBullet;
class Wave;
class TileMap;
class HealItem;
class SpriteGo;
class AmmoItem;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	Zombie* zombie;
	TextScore* textScore;
	HpBar* hpbar;
	TextBullet* textBullet;
	Wave* wave;
	TileMap* tileMap;
	HealItem* healItem;
	SpriteGo* cursor;
	AmmoItem* Ammoitem;

	float timer = 0.f;

	int waveValue;
	int zombieCount;
 	sf::Vector2f cellCount;

	bool gameStop;
public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void WaveUpgrade();
};

