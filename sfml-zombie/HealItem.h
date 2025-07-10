#pragma once
#include "Item.h"
#include "HitBox.h"



class Player;
class HealItem : public Item
{
protected:

	

public:
	static int healamount;
	HealItem(const std::string& name = "");
	virtual ~HealItem() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void UseItem(Player* player) override;

	sf::FloatRect GetLocalBounds() const override // 로컬 좌표계에서의 경계 사각형을 반환
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override // 전역 좌표계에서의 경계 사각형을 반환
	{
		return body.getGlobalBounds();
	}
	
	void UpGradeHealAmount(int up) { 
		healamount += up; 
		std::cout << healamount << std::endl;
	}

};

