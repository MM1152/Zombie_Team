#pragma once
#include "Item.h"


class Player;
class HealItem : public Item
{
protected:

	sf::Sprite body;
	std::string texId = "graphics/health_pickup.png";
	int healamount = 0;
	bool isActive = false;
	Player* player;

	HitBox hitbox; // ��Ʈ�ڽ� �߰�

public:
	HealItem(const std::string& name = "");
	virtual ~HealItem() = default;

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

	void UseItem(int amount) override;

	sf::FloatRect GetLocalBounds() const override // ���� ��ǥ�迡���� ��� �簢���� ��ȯ
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override // ���� ��ǥ�迡���� ��� �簢���� ��ȯ
	{
		return body.getGlobalBounds();
	}
};

