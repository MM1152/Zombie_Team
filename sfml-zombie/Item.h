#pragma once
#include "GameObject.h"
#include "HitBox.h"

enum class ItemType
{
	Heal,
	Ammo,
};


class Item : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId;
	int amount = 0;
	bool isActive = false;

	HitBox hitbox;
public:

	Item(const std::string& name="");
	virtual ~Item() = default;


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

	virtual void UseItem(int amount) = 0;

	sf::FloatRect GetLocalBounds() const override // 로컬 좌표계에서의 경계 사각형을 반환
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override // 전역 좌표계에서의 경계 사각형을 반환
	{
		return body.getGlobalBounds();
	}
};

