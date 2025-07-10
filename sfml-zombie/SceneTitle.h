#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "Button.h"
class SceneTitle : public Scene
{
protected:
	TextGo* title;
	Button* startText;
	Button* exitText;
	
	sf::Vector2f windowSize;
public:
	SceneTitle();
	
	void ChangeScene();
	void Enter() override;
	void Init() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

