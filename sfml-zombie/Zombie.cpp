#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"
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
	targetPos = { 0.f , 0.f };
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetType((Types)Utils::RandomRange(0, (int)Types::TypeCount));
	body.setTexture(TEXTURE_MGR.Get(texId) , true);
	
	SetOrigin(Origins::MC);
}

void Zombie::Update(float dt)
{	
	//TODO : �÷��̾� �ǽð� ��ġ������ ����
	dir = player->GetPosition() - GetPosition();
	Utils::Normalize(dir);
	SetPosition(GetPosition() + dir * speed * dt);
	SetRotation(Utils::Angle(dir));

	hitBox.UpdateTransform(body, { GetLocalBounds().left + 10.f , GetLocalBounds().top + -10.f  , GetLocalBounds().width - 10.f, GetLocalBounds().height - 10.f }); // ��Ʈ�ڽ� ũ������
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Zombie::SetType(Types type)
{
	if (type == Types::Bloater) {
		maxHp = 500;
		hp = maxHp;
		damage = 50;
		speed = 30;
		texId = "graphics/bloater.png";
	}
	else if (type == Types::Chaser) {
		maxHp = 200;
		hp = maxHp;
		damage = 30;
		speed = 50;
		texId = "graphics/chaser.png";
	}
	else if (type == Types::Crawler) {
		maxHp = 60;
		hp = maxHp;
		damage = 10;
		speed = 65;
		texId = "graphics/crawler.png";
	}

}

void Zombie::OnDamage(int damage)
{
	std::cout << damage << std::endl;
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0) {
		SetActive(false);
	}
}

void Zombie::SetPlayer(Player* player)
{
	this->player = player;
}
