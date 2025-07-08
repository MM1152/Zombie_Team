#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Bullet.h"

SceneGame::SceneGame(): Scene(SceneIds::Game)
{
}


void SceneGame::Init()
{
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x , FRAMEWORK.GetWindowSizeF().y }); // 얘네 추가하면 안납작함
	worldView.setCenter({ 0.f , 0.f });

	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/bullet.png");

	player = (Player*)AddGameObject(new Player("Player"));

}


void SceneGame::Enter()
{
	Scene::Enter(); // 항상 부모의 클래스 enter를 호출해야 합니다.
}



void SceneGame::Exit()
{

}



void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}




void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
					 
				