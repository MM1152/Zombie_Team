#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "Button.h"

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
	text = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));
	text2 = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));
	//exit = (TextGo*)(AddGameObject(new TextGo("fonts/zombiecontrol.ttf")));
	
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	text->setShapeSize({ 200.f,200.f });
	text->setShapeFillColor(sf::Color::Blue);
	text->setShapePosition({ bounds.width * 0.8f, bounds.height * 0.8f });
	text->setShapeOrigin();
	
	text->setText("Start");
	text->setCharacterSize(text->GetShape());
	text->setTextFillColor(sf::Color::Black);
	text->setTextPosition(text->GetShape());
	text->setTextOrigin(Origins::MC);
	//AddGameObject(text);

	text2->setShapeSize({ 200.f,200.f });
	text2->setShapeFillColor(sf::Color::Blue);
	text2->setShapePosition({ bounds.width * 0.2f, bounds.height * 0.8f });
	text2->setShapeOrigin();
	
	text2->setText("Exit");
	text2->setCharacterSize(text2->GetShape());
	text2->setTextFillColor(sf::Color::Black);
	text2->setTextPosition(text2->GetShape());
	text2->setTextOrigin(Origins::MC);
	//AddGameObject(text2);

	windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

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
	if (text->GetIsPressed())
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	if (text2->GetIsPressed())
	{
		FRAMEWORK.GetWindow().close();
	}
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	Scene::Draw(window);
}