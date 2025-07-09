#include "stdafx.h"
#include "Item.h"
#include "HealItem.h"
#include "AmmoItem.h"

Item::Item(const std::string& name, const std::string& texId)
	: GameObject(name)
	, texId(texId)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Item::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Item::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Item::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Item::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Item::Init()
{
}

void Item::Release()
{
}

void Item::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

}

void Item::Update(float dt)
{
	hitBox.UpdateTransform(body, GetGlobalBounds()); // 히트박스 업데이트

}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

Item& Item::SpawnItem()
{
	int rand = Utils::RandomRange(0, 2);
	if (rand == 0)
	{
		Item* item = new HealItem();
		return *item;
	}
	if (rand == 1)
	{
		Item* item = new AmmoItem();
		return *item;
	}

}
