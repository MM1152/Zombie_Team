#pragma once
#include "GameObject.h"



class SceneGame;



class Player : public GameObject
{
protected:
	sf::Sprite body; // 플레이어 스프라이트
	std::string texId = "graphics/player.png"; // 플레이어 텍스처 ID

	sf::Vector2f direction; // 플레이어 이동 방향
	sf::Vector2f look; // 플레이어 시선 방향

	int hp = 0;
	int maxHp = 1000;
	bool isAlive = true; // 플레이어 생존 여부


	float speed = 200.f;
	float shootInterval = 0.1f; // 총알 발사 간격
	float shootTimer = 0.f; // 총알 발사 타이머


	SceneGame* sceneGame = nullptr; // 플레이어가 속한 게임 씬

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

