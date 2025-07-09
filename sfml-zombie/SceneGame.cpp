#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include "TextScore.h"
#include "HpBar.h"
#include "TextBullet.h"
#include "TileMap.h"
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
	fontIds.push_back("fonts/zombiecontrol.ttf");

	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/background_sheet.png");

	textScore = new TextScore();
	hpbar = new HpBar();
	textBullet = new TextBullet();


	AddGameObject(textBullet);
	AddGameObject(hpbar);
	AddGameObject(textScore);
	player = (Player*)AddGameObject(new Player("Player"));
	AddGameObject(new TileMap("TileMap"));

	ZOMBIE_MGR.SettingScene(this);
	ZOMBIE_MGR.SettingPlayer(player);
	Scene::Init();
}


void SceneGame::Enter()
{
	ZOMBIE_MGR.Enter();
	Scene::Enter(); // 항상 부모의 클래스 enter를 호출해야 합니다.
}



void SceneGame::Exit()
{
	Scene::Exit();
}



void SceneGame::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space)) {
		ZOMBIE_MGR.SpawnZombie(1);
		textBullet->SetBulletCount(10, 20);
	}
	
	int count = ZOMBIE_MGR.GetDieZombieCount();
	textScore->SetScore(count * 10.f);
	worldView.setCenter(player->GetPosition());
	Scene::Update(dt);
}


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
					 
				