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
	sf::Vector2f startPos = { bounds.width * 0.5f,bounds.height * 0.3f };

	start->SetString("Start");
	start->SetCharacterSize(200);
	start->SetFillColor(sf::Color::Black);
	start->SetOrigin(Origins::MC);
	start->SetPosition(startPos);

	Scene::Enter();
}

void SceneTitle::Init()
{
	texIds.push_back("graphics/background.png");
	fontIds.push_back("fonts/zombiecontrol.ttf");
	sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
	FRAMEWORK.GetWindow().setView(view);
	Scene::Init();
	
}

void SceneTitle::Update(float dt)
{
	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
}
