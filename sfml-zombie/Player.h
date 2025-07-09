#pragma once
#include "GameObject.h"
#include "TextBullet.h"
#include "HitBox.h"
#include "TileMap.h"
#include "Item.h"
#include "HealItem.h"
#include "AmmoItem.h"

class SceneGame;
class Bullet;
class HpBar;
class TextBullet;
class HealItem;

class Player : public GameObject
{
protected:
	sf::Sprite body; 
	std::string texId = "graphics/player.png"; 

	sf::Vector2f direction; 
	sf::Vector2f look; 

	HpBar* hpbar;

	HitBox hitBox; 
	TileMap* tileMap;

	int hp = 0;
	int maxHp = 1000;
	int healamount = 100;
	int Ammoamount;
	bool isAlive = true; 

	float speed = 200.f;
	
	float hitInterval = 0.2f;
	float hitTimer = 0.f;
	float shootInterval = 0.1f; 
	float shootTimer = 0.f; 

	Bullet* bullet;
	SceneGame* sceneGame = nullptr; 

	std::list<Bullet*> bulletList; 
	std::list<Bullet*> bulletPool; 

	TextBullet* textBullet; 

	int curBullet = 0;
	int maxBullet = 20;
	float reloadTime = 1.0f; 
	bool isReloading = false; 
	float reloadTimer = 0.f; 

	std::list<Item*> itemList;
public:
	bool hitAble = false;
	Player(const std::string& name = "");
	virtual ~Player() = default;

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

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}
	const HitBox& GetHitBox() const
	{
		return hitBox;
	}

	void SettingHpBar(HpBar* hpBar);
	void Shoot();
	void OnDamage(int damage);
	void SetTextBullet(TextBullet* textBullet);
	void SetItem(Item* item);

	void Heal(int healamount);
	void Ammo(int Ammoamount);

};

