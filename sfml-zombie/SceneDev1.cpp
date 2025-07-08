#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Zombie.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

SceneDev1::~SceneDev1()
{

}

void SceneDev1::Init()
{
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");

	Scene::Init();
}

void SceneDev1::Enter()
{
	zombie = new Zombie();
	AddGameObject(zombie);

	Scene::Enter();
}

void SceneDev1::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space)) {
		zombie->Reset();
	}
	Scene::Update(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
