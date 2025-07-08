#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Zombie.h"
#include "TextScore.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

SceneDev1::~SceneDev1()
{

}

void SceneDev1::Init()
{
	ZOMBIE_MGR.SettingScene(this);
	worldView.setCenter(0.f, 0.f);
	worldView.setSize({FRAMEWORK.GetWindowSizeF().x, FRAMEWORK.GetWindowSizeF().y });

	uiView.setSize({ FRAMEWORK.GetWindowSizeF().x, FRAMEWORK.GetWindowSizeF().y });
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2, FRAMEWORK.GetWindowSizeF().y / 2 });

	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/blood.png");
	fontIds.push_back("fonts/zombiecontrol.ttf");

	Scene::Init();
}

void SceneDev1::Enter()
{
	textScore = new TextScore();
	textScore->SetPosition({0.f , 0.f});
	AddGameObject(textScore);
	
	Scene::Enter();
}

void SceneDev1::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space)) {
		ZOMBIE_MGR.SpawnZombie(1);
	}
	
	Scene::Update(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
