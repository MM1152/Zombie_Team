#pragma once
#include "GameObject.h"
class Zombie : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId;

	int maxHp;
	int hp;

	float speed;
	// 플레이어 연결 필요
public:
	enum class Types {
		Bloater,
		Chaser,
		Crawler,
		TypeCount,
	};

	Zombie(const std::string& name = "");
	virtual ~Zombie() = default;

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

	void SetType(Types type);
	void OnDamage(int damage);
};

