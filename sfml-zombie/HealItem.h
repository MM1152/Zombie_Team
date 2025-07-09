#pragma once
#include "Item.h"
#include "HitBox.h"



class Player;
class HealItem : public Item
{
protected:

	int healamount = 100;

public:
	HealItem(const std::string& name = "");
	virtual ~HealItem() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void UseItem(Player* player) override;

	sf::FloatRect GetLocalBounds() const override // ���� ��ǥ�迡���� ��� �簢���� ��ȯ
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override // ���� ��ǥ�迡���� ��� �簢���� ��ȯ
	{
		return body.getGlobalBounds();
	}
	

};

