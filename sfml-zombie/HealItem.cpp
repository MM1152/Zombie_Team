#include "stdafx.h"
#include "HealItem.h"
#include "Player.h"

HealItem::HealItem(const std::string& name)
	: Item(name)
{
}

void HealItem::SetPosition(const sf::Vector2f& pos)
{
	Item::SetPosition(pos);
	body.setPosition(pos);
}

void HealItem::SetRotation(float rot)
{
	Item::SetRotation(rot);
	body.setRotation(rot);
}

void HealItem::SetScale(const sf::Vector2f& s)
{
	Item::SetScale(s);
	body.setScale(s);
}

void HealItem::SetOrigin(const sf::Vector2f& o)
{
	Item::SetOrigin(o);
	body.setOrigin(o);
}

void HealItem::SetOrigin(Origins preset)
{
	Item::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}


void HealItem::Init()
{
	healamount = 500;

}

void HealItem::Release()
{
}

void HealItem::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
}

void HealItem::Update(float dt)
{
}

void HealItem::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void HealItem::UseItem(int amount)
{
	int curHp = 0;
	int maxHp = 0;
	player->GetCurrentHp(curHp, maxHp);

	if (healamount > (maxHp - curHp))
	{
		curHp = maxHp;
	}
	else
	{
		curHp += healamount;
	}
}
