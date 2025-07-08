#pragma once
#include "Scene.h"
#include "TextGo.h"
class SceneTitle : public Scene
{
protected:
	TextGo* title;
	TextGo* start;
	TextGo* exit;
	

public:
	SceneTitle();
	
	void ChangeScene();
	void Enter() override;
	void Init() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

