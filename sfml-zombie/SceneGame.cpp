#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include "TextScore.h"
#include "HpBar.h"
#include "TextBullet.h"
#include "TileMap.h"
#include "Button.h" 
#include "Wave.h"
#include "Item.h"
#include "HealItem.h"
#include "SpriteGo.h"
SceneGame::SceneGame(): Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x , FRAMEWORK.GetWindowSizeF().y }); // ��� �߰��ϸ� �ȳ�����
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
	texIds.push_back("graphics/background.png");

	fontIds.push_back("fonts/zombiecontrol.ttf");


	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/health_pickup.png");

	
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
	AddGameObject(player);
	AddGameObject(wave);
	AddGameObject(cursor);

	healItem = new HealItem("HealItem");
	AddGameObject(healItem);

	ZOMBIE_MGR.SettingScene(this);
	ZOMBIE_MGR.SettingPlayer(player);
	player->SettingHpBar(hpbar);

	player->SetTextBullet(textBullet); // 플레이어에 연결해야 SetBulletCount(int curCount, int maxCount) 가 업데이트됨

	Scene::Init();
}

void SceneGame::Enter()
{
	
	ZOMBIE_MGR.Enter();
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	back = (SpriteGo*)AddGameObject(new SpriteGo("graphics/background.png"));

	waveValue = 1;
	cellCount = { 10 , 10 };

	zombieCount = waveValue * 5;

	gameStop = false;
	
	// 여기에 넣어둘게 너무 길어질거 같아서 접어둘거임
#pragma region UpGradeText
	upGrade1 = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));
	upGrade2 = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));
	upGrade3 = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));
	upGrade4 = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));
	upGrade5 = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));
	upGrade6 = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	// Up1
	upGrade1->setShapeSize({ 200.f,200.f });
	upGrade1->setShapeFillColor(sf::Color::Blue);
	upGrade1->setShapePosition({ bounds.width * 0.5f, bounds.height * 0.1f });
	upGrade1->setShapeOrigin();
	
	upGrade1->setCharacterSize(upGrade1->GetShape());
	upGrade1->setText("INCREASED RATE OF FIRE");
	upGrade1->setTextFillColor(sf::Color::Red);
	upGrade1->setTextPosition(upGrade1->GetShape());
	upGrade1->setTextOrigin(Origins::MC);
	upGrade1->SetActive(false);
	upGrade1->setButtonPtr([] {
			
		});
	
	// Up2
	upGrade2->setShapeSize({ 200.f,200.f });
	upGrade2->setShapeFillColor(sf::Color::Blue);
	upGrade2->setShapePosition({ bounds.width * 0.5f, bounds.height * 0.3f });
	upGrade2->setShapeOrigin();
		   
	upGrade2->setCharacterSize(upGrade2->GetShape());
	upGrade2->setText("INCREASED CLIP SIZE (NEXT RELOAD)");
	upGrade2->setTextFillColor(sf::Color::Red);
	upGrade2->setTextPosition(upGrade2->GetShape());
	upGrade2->setTextOrigin(Origins::MC);
	upGrade2->SetActive(false);

	// Up3
	upGrade3->setShapeSize({ 200.f,200.f });
	upGrade3->setShapeFillColor(sf::Color::Blue);
	upGrade3->setShapePosition({ bounds.width * 0.5f, bounds.height * 0.5f });
	upGrade3->setShapeOrigin();
		   
	upGrade3->setCharacterSize(upGrade3->GetShape());
	upGrade3->setText("INCREASED MAX HEALTH");
	upGrade3->setTextFillColor(sf::Color::Red);
	upGrade3->setTextPosition(upGrade3->GetShape());
	upGrade3->setTextOrigin(Origins::MC);
	upGrade3->SetActive(false);

	// Up4
	upGrade4->setShapeSize({ 200.f,200.f });
	upGrade4->setShapeFillColor(sf::Color::Blue);
	upGrade4->setShapePosition({ bounds.width * 0.5f, bounds.height * 0.7f });
	upGrade4->setShapeOrigin();
		   
	upGrade4->setCharacterSize(upGrade4->GetShape());
	upGrade4->setText("INCREASED RUN SPEED");
	upGrade4->setTextFillColor(sf::Color::Red);
	upGrade4->setTextPosition(upGrade4->GetShape());
	upGrade4->setTextOrigin(Origins::MC);
	upGrade4->SetActive(false);

	// Up5
	upGrade5->setShapeSize({ 200.f,200.f });
	upGrade5->setShapeFillColor(sf::Color::Blue);
	upGrade5->setShapePosition({ bounds.width * 0.5f, bounds.height * 0.9f });
	upGrade5->setShapeOrigin();
		   
	upGrade5->setCharacterSize(upGrade5->GetShape());
	upGrade5->setText("MORE AND BETTER HEALTH PICKUPS");
	upGrade5->setTextFillColor(sf::Color::Red);
	upGrade5->setTextPosition(upGrade5->GetShape());
	upGrade5->setTextOrigin(Origins::MC);
	upGrade5->SetActive(false);

	// Up6
	upGrade6->setShapeSize({ 200.f,200.f });
	upGrade6->setShapeFillColor(sf::Color::Blue);
	upGrade6->setShapePosition({ bounds.width * 0.5f, bounds.height * 1.0f });
	upGrade6->setShapeOrigin();
		   
	upGrade6->setCharacterSize(upGrade6->GetShape());
	upGrade6->setText("MORE AND BETTER AMMO PICKUPS");
	upGrade6->setTextFillColor(sf::Color::Red);
	upGrade6->setTextPosition(upGrade6->GetShape());
	upGrade6->setTextOrigin(Origins::MC);
	upGrade6->SetActive(false);
#pragma endregion

	Scene::Enter(); // �׻� �θ��� Ŭ���� enter�� ȣ���ؾ� �մϴ�.

	back->sortingLayer = SortingLayers::UI;
	back->sortingOrder = 0;
	back->SetPosition({ 0.f,0.f });
	back->SetActive(false);

	tileMap->Set((sf::Vector2i)cellCount, { 50, 50 });
	wave->SetWaveString(waveValue);
	wave->SetZombieCount(zombieCount);
	wave->SetPosition({ FRAMEWORK.GetWindowSizeF().x - 500.f, FRAMEWORK.GetWindowSizeF().y - 200.f });
	ZOMBIE_MGR.SpawnZombie(zombieCount, cellCount.x * 50.f / 2.5f);
	//Scene::Enter(); // 항상 부모의 클래스 enter를 호출해야 합니다.
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

	if (zombieCount == 0) 
	{
		gameStop = true;
		upGrade1->SetActive(true);
		upGrade2->SetActive(true);
		upGrade3->SetActive(true);
		upGrade4->SetActive(true);
		upGrade5->SetActive(true);
		upGrade6->SetActive(true);
		back->SetActive(true);
	}

	if (gameStop && InputMgr::GetKeyDown(sf::Keyboard::Enter)) 
	{
		// 업그레이드 화면
		WaveUpgrade();
		gameStop = false;
		upGrade1->SetActive(false);
		upGrade2->SetActive(false);
		upGrade3->SetActive(false);
		upGrade4->SetActive(false);
		upGrade5->SetActive(false);
		upGrade6->SetActive(false);
		back->SetActive(false);
	}
	
	worldView.setCenter(player->GetPosition());
	
	cursor->SetPosition((sf::Vector2f)ScreenToWorld(InputMgr::GetMousePosition()));
	Scene::Update(dt);
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

void SceneGame::Upgrade()
{

}


//void SceneGame::Draw(sf::RenderWindow& window)
//{
//	Scene::Draw(window);
//}
					 
				