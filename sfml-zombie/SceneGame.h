#pragma once
#include "Scene.h"
#include "Item.h"
#include "Button.h"

class Player;
class Button;
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
	Player* player;
	Button* button = nullptr;
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

	SpriteGo* back;

	// ¹è¿­
	Button* upGrade1;
	Button* upGrade2;
	Button* upGrade3;
	Button* upGrade4;
	Button* upGrade5;
	Button* upGrade6;

	
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
	bool GetGameStop() const { return gameStop; }
	void WaveUpgrade();
	void Upgrade();

	static void SetPlayerFireSpeed();
};
