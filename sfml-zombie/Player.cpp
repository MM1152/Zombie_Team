#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"


Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}



void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	
}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else
	{
		sceneGame = nullptr;
	}


	body.setTexture(TEXTURE_MGR.Get(texId), true); // 텍스처 재설정
	SetOrigin(Origins::MC);
	SetRotation(0.f);

}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal); 
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f) // 방향 벡터의 크기가 1보다 크면
	{
		Utils::Normalize(direction); // 방향 벡터를 정규화
	}
	SetPosition(position + direction * speed * dt); // 플레이어 위치 업데이트



	sf::Vector2i mousePosition = InputMgr::GetMousePosition(); // 마우스 위치 가져오기
	sf::Vector2f mouseWorldPosition = sceneGame->ScreenToWorld(mousePosition); // 월드 좌표로 변환
	look = Utils::GetNormal(mouseWorldPosition - GetPosition()); // 플레이어가 바라보는 방향 계산
	SetRotation(Utils::Angle(look)); // 플레이어 회전 설정
	
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}