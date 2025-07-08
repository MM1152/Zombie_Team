#include "stdafx.h"
#include "Zombie.h"

Zombie::Zombie(const std::string& name)
	:GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	rotation = rot;
	body.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.scale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	origin = o;
	originPreset = Origins::Custom;
	body.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	originPreset = preset;
	Utils::SetOrigin(body , preset);
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	SetType((Types)Utils::RandomRange(0, (int)Types::TypeCount));
	SetScale({ 1.f,1.f });
	body.setTexture(TEXTURE_MGR.Get(texId) , true);
	
	SetOrigin(Origins::MC);
	SetPosition({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });
}

void Zombie::Update(float dt)
{
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Zombie::SetType(Types type)
{
	if (type == Types::Bloater) {
		maxHp = 500;
		hp = maxHp;

		speed = 100;
		texId = "graphics/bloater.png";
	}
	else if (type == Types::Chaser) {
		maxHp = 200;
		hp = maxHp;

		speed = 200;
		texId = "graphics/chaser.png";
	}
	else if (type == Types::Crawler) {
		maxHp = 100;
		hp = maxHp;

		speed = 300;
		texId = "graphics/crawler.png";
	}

}

void Zombie::OnDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0) {
		//TODO : Á»ºñ ÇÇ»Ì±â
	}
}
