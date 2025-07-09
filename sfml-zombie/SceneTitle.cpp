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
	startText = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));
	exitText = (Button*)(AddGameObject(new Button("fonts/zombiecontrol.ttf")));
	//exit = (TextGo*)(AddGameObject(new TextGo("fonts/zombiecontrol.ttf")));
	
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	startText->setShapeSize({ 200.f,200.f });
	startText->setShapeFillColor(sf::Color::Blue);
	startText->setShapePosition({ bounds.width * 0.8f, bounds.height * 0.8f });
	startText->setShapeOrigin();
	

	startText->setCharacterSize(startText->GetShape());
	startText->setText("Start");
	startText->setTextFillColor(sf::Color::Black);
	startText->setTextPosition(startText->GetShape());
	startText->setTextOrigin(Origins::MC);
	//AddGameObject(text);

	exitText->setShapeSize({ 200.f,200.f });
	exitText->setShapeFillColor(sf::Color::Blue);
	exitText->setShapePosition({ bounds.width * 0.2f, bounds.height * 0.8f });
	exitText->setShapeOrigin();
	
	exitText->setCharacterSize(exitText->GetShape());
	exitText->setText("Exit");
	exitText->setTextFillColor(sf::Color::Black);
	exitText->setTextPosition(exitText->GetShape());
	exitText->setTextOrigin(Origins::MC);
	//AddGameObject(text2);

	startText->setButtonPtr([] {
		SCENE_MGR.ChangeScene(SceneIds::Game);
	});

	exitText->setButtonPtr([] {
		FRAMEWORK.GetWindow().close();
	});
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
	/*if (startText->GetIsPressed())
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	if (exitText->GetIsPressed())
	{
		FRAMEWORK.GetWindow().close();
	}*/
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	Scene::Draw(window);
}