#include "stdafx.h"
#include "HpBar.h"

HpBar::HpBar(const std::string& name)
	: GameObject(name)
{
}

void HpBar::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	rect.setPosition(pos);
}

void HpBar::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	rect.setRotation(rot);
}

void HpBar::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	rect.setScale(s);
}

void HpBar::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	rect.setOrigin(o);
}

void HpBar::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(rect, preset);
	}
}

void HpBar::Init()
{
	initSize = { 400 , 80 };
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	SetOrigin(Origins::ML);
}

void HpBar::Release()
{
}

void HpBar::Reset()
{
	initSize = { 400 , 80 };
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	SetOrigin(Origins::ML);
	rect.setFillColor(sf::Color::Red);
	rect.setSize(initSize);

	SetPosition({ FRAMEWORK.GetWindowSizeF().x / 2 ,FRAMEWORK.GetWindowSizeF().y - 100.f });
}

void HpBar::Update(float dt)
{
	//TODO : 플레이어 연결 하고 HP 받아오기 필요
}

void HpBar::Draw(sf::RenderWindow& window)
{
	window.draw(rect);
}

void HpBar::SettingHp(int hp, int maxHp)
{
	rect.setSize({ initSize.x * (hp / (float)maxHp) , initSize.y });
}
