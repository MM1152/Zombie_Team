#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "TextBullet.h"


Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}



void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	
}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game) // �� �ʱ�ȭ
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else
	{
		sceneGame = nullptr;
	}

	for (Bullet* bullet : bulletList) // bulletList�� �ִ� ��� �Ѿ��� ��Ȱ��ȭ�ϰ� bulletPool�� �ִ´�.
	{
		bullet->SetActive(false); 
		bulletPool.push_back(bullet); 
	}
	bulletList.clear();


	body.setTexture(TEXTURE_MGR.Get(texId), true); // �ؽ�ó �缳��
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);

	direction = { 0.f, 0.f };
	look = { 1.f, 0.f };

	shootTimer = 0.f;
	shootInterval = 0.1f; 

	hp = maxHp;		
	 
	 

}




void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal); 
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f) // ���� ������ ũ�Ⱑ 1���� ũ��
	{
		Utils::Normalize(direction); // ���� ���͸� ����ȭ
	}
	SetPosition(position + direction * speed * dt); // �÷��̾� ��ġ ������Ʈ


	auto it = bulletList.begin(); // �Ѿ� ����Ʈ�� ��ȸ�ϴ� �ݺ���, �Ҹ�����Ʈ���� �Ѿ� �ϳ��� ������ ��Ȱ��ȭ �Ǿ� ������ Pool�� ����ְ� ����Ʈ���� ����, Ȱ��ȭ �Ǿ������� �Ѿ
	while (it != bulletList.end()) // ��Ȱ��ȭ�� ������Ʈ�� ���ִ� ��� ��Ȱ���ϱ� ���� ���� ��Ƶδ� ��.
	{
		if (!(*it)->GetActive())
		{
			bulletPool.push_back(*it);
			it = bulletList.erase(it);
		}
		else
		{
			++it;
		}
	}


	sf::Vector2i mousePosition = InputMgr::GetMousePosition(); // ���콺 ��ġ ��������
	sf::Vector2f mouseWorldPosition = sceneGame->ScreenToWorld(mousePosition); // ���� ��ǥ�� ��ȯ
	look = Utils::GetNormal(mouseWorldPosition - GetPosition()); // �÷��̾ �ٶ󺸴� ���� ���
	SetRotation(Utils::Angle(look)); // �÷��̾� ȸ�� ����
	
	shootTimer += dt; // ���� Ÿ�̸� ������Ʈ
	if(InputMgr::GetMouseButton(sf::Mouse::Left) && shootTimer>shootInterval)
	{
		Shoot();
		shootTimer = 0.f;	
	}

}


void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}


void Player::Shoot()
{
	Bullet* bullet = nullptr;
	if(bulletPool.empty()) // �Ѿ��� ������ ���� ����
	{
		bullet = new Bullet(); // �Ѿ� ��ü ����
		bullet->Init(); 
	}
	else // �Ѿ��� ������ Ǯ���� ��������
	{
		bullet = bulletPool.front(); // Ǯ���� ù ��° �Ѿ� ��������
		bulletPool.pop_front(); // �Ѿ� Ǯ���� ����
		bullet->SetActive(true); // �Ѿ� Ȱ��ȭ
	}

	bullet->Reset();
	bullet->Fire(position + look * 10.f, look, 1000.f, 10);

	bulletList.push_back(bullet); // �Ѿ� ����Ʈ�� �߰�
	sceneGame->AddGameObject(bullet);
}

void Player::OnDamage(int damage)
{
	if (!isAlive)
	{
		return;
	}

	hp = Utils::Clamp(hp - damage, 0, maxHp); 
	if (hp <= 0)
	{
		hp = 0;
		isAlive = false; // �÷��̾ �׾����� ǥ��
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}
