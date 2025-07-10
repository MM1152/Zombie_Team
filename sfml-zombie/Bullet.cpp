#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "ZombieMgr.h"
#include "Zombie.h"

float Bullet::speed = 100;
int Bullet::damage = 10;

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
	sortingLayer = SortingLayers::Foreground; // ���� ���̾� ����
	sortingOrder = 1;
}


void Bullet::Release()
{
}

void Bullet::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId), true); // �ؽ�ó �缳��
	SetOrigin(Origins::ML);
	SetPosition(sf::Vector2f( 0.f, 0.f ));
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	direction = { 0.f,0.f };
	speed = 0.f;
	damage = 100;
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt); // ��ġ ������Ʈ
	hitBox.UpdateTransform(body, GetGlobalBounds()); // ��Ʈ�ڽ� ������Ʈ

	const auto& list = ZOMBIE_MGR.GetZombieList();
	for(Zombie* zombie : list )
	{
		if (!zombie->GetActive())
			continue;

		if (hitBox.rect.getGlobalBounds().intersects(zombie->GetHitBox().rect.getGlobalBounds())) // ��Ʈ�ڽ� �浹 üũ 
		{
			SetActive(false); // �Ѿ� ��Ȱ��ȭ
			zombie->OnDamage(damage); // ���񿡰� ������ ����
			break; 
		}
	}

}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float spd, int dmg)
{
	SetPosition(pos); // �߻� ��ġ ����
	direction = dir; // �߻� ���� ����
	speed = spd;
	damage = dmg;

	SOUND_MGR.Play(Audio::SHOOT);
	SetRotation(Utils::Angle(direction)); // ���⿡ ���� ȸ�� ���� 
}

