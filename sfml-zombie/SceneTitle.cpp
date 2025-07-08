#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::ChangeScene()
{
}

void SceneTitle::Enter()
{
	AddGameObject(new SpriteGo("graphics/background.png"));
	start = (TextGo*)(AddGameObject(new TextGo("fonts/zombiecontrol.ttf")));
	exit = (TextGo*)(AddGameObject(new TextGo("fonts/zombiecontrol.ttf")));
	
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	sf::Vector2f startPos = { bounds.width * 0.5f,bounds.height * 0.5f };
	sf::Vector2f exitPos = { bounds.width * 0.5f,bounds.height * 0.7f };

	start->SetString("Start");
	start->SetCharacterSize(150);
	start->SetFillColor(sf::Color::White);
	start->SetOrigin(Origins::MC);
	start->SetPosition(startPos);

	exit->SetString("Exit");
	exit->SetCharacterSize(150);
	exit->SetFillColor(sf::Color::White);
	exit->SetOrigin(Origins::MC);
	exit->SetPosition(exitPos);

	windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	Scene::Enter();
}

void SceneTitle::Init()
{
	texIds.push_back("graphics/background.png");
	fontIds.push_back("fonts/zombiecontrol.ttf");
	Scene::Init();
}

void SceneTitle::Update(float dt)
{
	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	Scene::Draw(window);
}