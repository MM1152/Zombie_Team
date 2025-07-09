#pragma once
#include "Item.h"
#include "HitBox.h"


class Player;
class AmmoItem : public Item
{
protected:

	int Ammoamount = 6;

public:
	AmmoItem(const std::string& name = "");
	virtual ~AmmoItem() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void UseItem(Player* player) override;


};

