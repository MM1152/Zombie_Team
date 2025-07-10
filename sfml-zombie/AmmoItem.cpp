#include "stdafx.h"
#include "AmmoItem.h"
#include "Player.h"

int AmmoItem::Ammoamount = 6;
AmmoItem::AmmoItem(const std::string& name)
	: Item(name, "graphics/ammo_pickup.png")
{
}

void AmmoItem::Init()
{

}

void AmmoItem::Release()
{
}

void AmmoItem::Reset()
{

	Item::Reset();
	SetOrigin(Origins::MC);
	SetPosition({ -100.f, -100.f });
	SetRotation(0.f);
	SetActive(true);
}

void AmmoItem::Update(float dt)
{
	hitBox.UpdateTransform(body, GetLocalBounds()); // 히트박스 업데이트
}


void AmmoItem::UseItem(Player* player)
{
	if (player)
	{
		player->Ammo(Ammoamount);
	}
}

