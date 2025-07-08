#pragma once
#include "Scene.h"

class TextGo;
class Zombie;
class SceneDev1 : public Scene
{
protected:
	Zombie* zombie;

public:
	SceneDev1();
	~SceneDev1() override;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

