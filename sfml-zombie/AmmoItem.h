#pragma once

#include "Item.h"
#include "HitBox.h"


class Player;
class AmmoItem : public Item
{
protected:

	

public:
	static int Ammoamount;
	AmmoItem(const std::string& name = "");
	virtual ~AmmoItem() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void UseItem(Player* player) override;
	void UpGradeAmmoAmount(int up) { 
		Ammoamount += up; 
		std::cout << Ammoamount << std::endl; 
	}

};

