#pragma once
#include "GameObject.h"



class SceneGame;



class Player : public GameObject
{
protected:
	sf::Sprite body; // �÷��̾� ��������Ʈ
	std::string texId = "graphics/player.png"; // �÷��̾� �ؽ�ó ID

	sf::Vector2f direction; // �÷��̾� �̵� ����
	sf::Vector2f look; // �÷��̾� �ü� ����

	int hp = 0;
	int maxHp = 1000;
	bool isAlive = true; // �÷��̾� ���� ����


	float speed = 200.f;
	float shootInterval = 0.1f; // �Ѿ� �߻� ����
	float shootTimer = 0.f; // �Ѿ� �߻� Ÿ�̸�


	SceneGame* sceneGame = nullptr; // �÷��̾ ���� ���� ��

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
};

