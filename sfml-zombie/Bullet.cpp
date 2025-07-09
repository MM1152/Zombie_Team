#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Bullet::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Bullet::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Bullet::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}




void Bullet::Init()
{
	sortingLayer = SortingLayers::Foreground; // 솔팅 레이어 설정
	sortingOrder = 1;
}




void Bullet::Release()
{
}

void Bullet::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId), true); // 텍스처 재설정
	SetOrigin(Origins::ML);
	SetPosition(sf::Vector2f( 0.f, 0.f ));
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	direction = { 0.f,0.f };
	speed = 0.f;
	damage = 0;
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt); // 위치 업데이트
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float spd, int dmg)
{
	SetPosition(pos); // 발사 위치 설정
	direction = dir; // 발사 방향 설정
	speed = spd;
	damage = dmg;

	SetRotation(Utils::Angle(direction)); // 방향에 따라 회전 설정 
}
