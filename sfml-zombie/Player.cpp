#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "HpBar.h"
#include "TextBullet.h"
#include "AmmoItem.h"


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

	curBullet = maxBullet;
}

void Player::Release()
{
}

void Player::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game) 
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else
	{
		sceneGame = nullptr;
	}

	for (Bullet* bullet : bulletList) 
	{
		bullet->SetActive(false); 
		bulletPool.push_back(bullet); 
	}
	bulletList.clear();
	ResetItem();

	body.setTexture(TEXTURE_MGR.Get(texId), true); 
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);

	direction = { 0.f, 0.f };
	look = { 1.f, 0.f };

	shootTimer = 0.f;
	shootInterval = 0.1f; 

	hitTimer = 0.f;
	hitInterval = 0.2f;
	hitAble = true;
	isAlive = true;
	hp = maxHp;
}



void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal); 
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	Utils::Normalize(direction); 
	SetPosition(GetPosition() + direction * speed * dt); 
	//std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;

	auto it = bulletList.begin(); 
	while (it != bulletList.end()) 
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
	SetRotation(Utils::Angle(look)); 
	
	hitBox.UpdateTransform(body, GetLocalBounds());	

	shootTimer += dt; 
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && shootTimer > shootInterval && curBullet > 0)
	{
		Shoot();
		shootTimer = 0.f;	
		curBullet--;
	}
	
	hitTimer += dt;
	if (hitInterval < hitTimer && !hitAble) {
		hitTimer = 0;
		hitAble = true;
	}
	

	if (textBullet)
	{
		textBullet->SetBulletCount(curBullet, maxBullet);
	}

	if (isReloading) 
	{
		reloadTimer += dt; 
		if (reloadTimer >= reloadTime) 
		{
			curBullet = maxBullet; 
			isReloading = false; 
			reloadTimer = 0.f; // ������ Ÿ�̸� �ʱ�ȭ
			SOUND_MGR.Play(Audio::RELOAD);
			if (textBullet)
			{
				textBullet->SetBulletCount(curBullet, maxBullet);
			}
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::R) && !isReloading)
	{

		isReloading = true; // ������ ���·� ����
		reloadTimer = 0.f; // ������ Ÿ�̸� �ʱ�ȭ
	}	


	std::list<Item*>::iterator itemIter = itemList.begin();

	while (itemIter != itemList.end()) {
		if (Utils::CheckCollision(hitBox.rect , (*itemIter)->GetHitBox().rect) && (*itemIter)->GetActive()) {
			(*itemIter)->UseItem(this);
			(*itemIter)->SetActive(false);
			sceneGame->RemoveGameObject(*itemIter);
			SOUND_MGR.Play(Audio::PICKUP);
			itemIter = itemList.erase(itemIter);

			hpbar->SettingHp(hp , maxHp);
		}
		else {
			itemIter++;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Player::SettingHpBar(HpBar* hpBar)
{
	this->hpbar = hpBar;
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
	bullet->Fire(position + look * 10.f, look, bulletSpeed, bulletDamage);

	bulletList.push_back(bullet); // �Ѿ� ����Ʈ�� �߰�
	sceneGame->AddGameObject(bullet);
}

void Player::OnDamage(int damage)
{
	
	if (!isAlive)
	{
		return;
	}
	
	hitAble = false;
	hp = Utils::Clamp(hp - damage, 0, maxHp); 
	
	if (hp <= 0)
	{
		hp = 0;
		
		isAlive = false;
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	hpbar->SettingHp(hp, maxHp);
}

void Player::SetTextBullet(TextBullet* textBullet) 
{
	this->textBullet = textBullet; 
}

void Player::ResetItem()
{
	std::list<Item*>::iterator itemIter = itemList.begin();

	while (itemIter != itemList.end()) {
		(*itemIter)->SetActive(false);
		sceneGame->RemoveGameObject(*itemIter);
		itemIter = itemList.erase(itemIter);
	}
	Item::fieldSpawnItemCount = 0;
}

void Player::SetItem(Item* item)
{
	itemList.push_back(item);
}

void Player::Heal(int healamount)
{
	hp += healamount;
}

void Player::Ammo(int Ammoamount)
{
	curBullet += Ammoamount;
	maxBullet += Ammoamount;
}
