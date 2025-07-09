#pragma once
#include "GameObject.h"
#include "TextBullet.h"
#include "HitBox.h"
#include "TileMap.h"

class SceneGame;
class Bullet;
class TextBullet;


class Player : public GameObject
{
protected:
	sf::Sprite body; // �÷��̾� ��������Ʈ
	std::string texId = "graphics/player.png"; // �÷��̾� �ؽ�ó ID

	sf::Vector2f direction; // �÷��̾� �̵� ����
	sf::Vector2f look; // �÷��̾� �ü� ����

	HitBox hitBox; // �繮 �߰�
	TileMap* tileMap;
	int hp = 0;
	int maxHp = 1000;
	bool isAlive = true; // �÷��̾� ���� ����

	float speed = 200.f;
	float shootInterval = 0.1f; // �Ѿ� �߻� ����
	float shootTimer = 0.f; // �Ѿ� �߻� Ÿ�̸�

	Bullet* bullet;
	SceneGame* sceneGame = nullptr; // �÷��̾ ���� ���� ��
	HitBox hitBox; // �÷��̾��� ��Ʈ�ڽ�

	std::list<Bullet*> bulletList; // �Ѿ� ����Ʈ
	std::list<Bullet*> bulletPool; // �Ѿ� Ǯ (������ ����)


	TextBullet* textBullet; 

	int curBullet = 0;
	int maxBullet = 20;
	float reloadTime = 1.5f; // ���� �ð�(��)
	bool isReloading = false; // ���� �� ����
	float reloadTimer = 0.f; 

public:
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

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}
	const HitBox& GetHitBox() const
	{
		return hitBox;
	}

	void Shoot();
	void OnDamage(int damage);
	void SetTextBullet(TextBullet* textBullet);


	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}


	const HitBox& GetHitBox() const
	{
		return hitBox;
	}


};

