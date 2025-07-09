#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include "TextScore.h"
#include "HpBar.h"
#include "TextBullet.h"
#include "TileMap.h"
#include "Wave.h"
#include "Item.h"
#include "HealItem.h"
#include "SpriteGo.h"
#include "AmmoItem.h"

SceneGame::SceneGame(): Scene(SceneIds::Game)
{
}


void SceneGame::Init()
{
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x , FRAMEWORK.GetWindowSizeF().y }); // 얘네 추가하면 안납작함
	worldView.setCenter({ 0.f , 0.f });

	uiView.setSize({ FRAMEWORK.GetWindowSizeF().x, FRAMEWORK.GetWindowSizeF().y });
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2, FRAMEWORK.GetWindowSizeF().y / 2 });

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/blood.png");
	texIds.push_back("graphics/ammo_icon.png");
	texIds.push_back("graphics/crosshair.png");

	fontIds.push_back("fonts/zombiecontrol.ttf");


	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/health_pickup.png");
	texIds.push_back("graphics/ammo_pickup.png");


	cursor = new SpriteGo("graphics/crosshair.png");
	textScore = new TextScore();
	hpbar = new HpBar();
	textBullet = new TextBullet();
	wave = new Wave();
	tileMap = new TileMap("TileMap");
	player = new Player("Player");


	AddGameObject(textBullet);
	AddGameObject(hpbar);
	AddGameObject(textScore);
	AddGameObject(player);
	AddGameObject(tileMap);
	AddGameObject(wave);

	AddGameObject(cursor);

	healItem = new HealItem("HealItem");
	Ammoitem = new AmmoItem("AmmoItem");

	

	ZOMBIE_MGR.SettingScene(this);
	ZOMBIE_MGR.SettingPlayer(player);
	player->SettingHpBar(hpbar);
	player->SetItem(healItem);
	player->SetItem(Ammoitem);
	player->SetTextBullet(textBullet); // 플레이어에 연결해야 SetBulletCount(int curCount, int maxCount) 가 업데이트됨



	Scene::Init();
}


void SceneGame::Enter()
{
	
	ZOMBIE_MGR.Enter();
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	wave->SetPosition({FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2});

	waveValue = 1;
	cellCount = { 10 , 10 };

	zombieCount = waveValue * 5;
	ZOMBIE_MGR.SpawnZombie(zombieCount , cellCount.x * 50.f / 2.5f);

	gameStop = false;

	Scene::Enter(); // �׻� �θ��� Ŭ���� enter�� ȣ���ؾ� �մϴ�.

	tileMap->Set((sf::Vector2i)cellCount, { 50, 50 });
	wave->SetWaveString(waveValue);
	wave->SetZombieCount(zombieCount);
	wave->SetPosition({ FRAMEWORK.GetWindowSizeF().x - 500.f, FRAMEWORK.GetWindowSizeF().y - 200.f });
	Scene::Enter(); // 항상 부모의 클래스 enter를 호출해야 합니다.
}



void SceneGame::Exit()
{
	Scene::Exit();
}



void SceneGame::Update(float dt)
{
	ZOMBIE_MGR.Update(dt);
	
	
	int count = ZOMBIE_MGR.GetDieZombieCount();
	zombieCount -= count;
	textScore->SetScore(count * 10.f);
	wave->SetZombieCount(zombieCount);

	if (zombieCount == 0) {
		gameStop = true;
	}

	if (gameStop && InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		WaveUpgrade();
		gameStop = false;
	}
	
	worldView.setCenter(player->GetPosition());
	
	cursor->SetPosition((sf::Vector2f)ScreenToWorld(InputMgr::GetMousePosition()));
	Scene::Update(dt);

	timer += dt;

	if (timer >= 2.f)
	{
		Item* item = Item::SpawnItem();
		if (item != nullptr) {
			item->Init();
			item->Reset();
			item->SetPosition(Utils::RandomInUnitCircle() * cellCount.x * 20.f);
			AddGameObject(item);
			timer = 0;
			player->SetItem(item);
		}
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::WaveUpgrade()
{
	waveValue++;
	cellCount = cellCount *  1.3f,
	tileMap->Set((sf::Vector2i)cellCount , { 50, 50 });
	tileMap->Reset();

	zombieCount = waveValue * 5;
	ZOMBIE_MGR.SpawnZombie(zombieCount , cellCount.x * 50.f / 2.5f);

	wave->SetWaveString(waveValue);
	wave->SetZombieCount(zombieCount);

	gameStop = false;
}

		 
				