#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Zombie; 
class SceneGame;
class Bullet : public GameObject
{
protected:
	sf::Sprite body; 
	std::string texId = "graphics/bullet.png"; //텍스처 아이디
	sf::Vector2f direction; //총알의 방향
	float speed = 0.f;
	int damage = 0;


	Zombie* zombie; //총알이 충돌한 좀비 객체

	SceneGame* sceneGame = nullptr;
	HitBox hitBox; //충돌 박스
public:
	Bullet(const std::string& name = "");
	virtual ~Bullet() = default;

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

	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float spd, int dmg);


	sf::FloatRect GetLocalBounds() const override // 로컬 좌표계에서의 경계 사각형을 반환
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override // 전역 좌표계에서의 경계 사각형을 반환
	{
		return body.getGlobalBounds();
	}
};

