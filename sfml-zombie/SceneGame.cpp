#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Bullet.h"

SceneGame::SceneGame(): Scene(SceneIds::Game)
{
}


void SceneGame::Init()
{
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x , FRAMEWORK.GetWindowSizeF().y }); // ��� �߰��ϸ� �ȳ�����
	worldView.setCenter({ 0.f , 0.f });

	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/bullet.png");

	player = (Player*)AddGameObject(new Player("Player"));

}


void SceneGame::Enter()
{
	Scene::Enter(); // �׻� �θ��� Ŭ���� enter�� ȣ���ؾ� �մϴ�.
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
					 
				