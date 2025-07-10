#include "stdafx.h"
#include "HealItem.h"
#include "Player.h"
#include "AmmoItem.h"

int HealItem::healamount = 100;
HealItem::HealItem(const std::string& name)
	: Item(name , "graphics/health_pickup.png")
{
}

void HealItem::Init()
{

}

void HealItem::Release()
{
}

void HealItem::Reset()
{
	Item::Reset();
	SetOrigin(Origins::MC);
	SetPosition({ 100.f, 100.f });
	SetRotation(0.f);
	SetActive(true);
}

void HealItem::Update(float dt)
{
	hitBox.UpdateTransform(body, GetLocalBounds()); // 히트박스 업데이트
}


void HealItem::UseItem(Player* player)
{
	if (player)
	{
		player->Heal(healamount);
	}
}
