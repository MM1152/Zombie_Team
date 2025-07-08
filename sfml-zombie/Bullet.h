#pragma once
#include "GameObject.h"


class SceneGame;
class Bullet : public GameObject
{
protected:

	sf::Sprite body; 
	std::string texId = "graphics/bullet.png"; //�ؽ�ó ���̵�
	sf::Vector2f direction; //�Ѿ��� ����
	float speed = 0.f;
	int damage = 0;

	SceneGame* sceneGame = nullptr;
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

	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed, int damage);
};

