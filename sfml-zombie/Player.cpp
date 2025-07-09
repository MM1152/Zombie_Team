#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "TextBullet.h"


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
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game) // 씬 초기화
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else
	{
		sceneGame = nullptr;
	}

	for (Bullet* bullet : bulletList) // bulletList에 있는 모든 총알을 비활성화하고 bulletPool에 넣는다.
	{
		bullet->SetActive(false); 
		bulletPool.push_back(bullet); 
	}
	bulletList.clear();


	body.setTexture(TEXTURE_MGR.Get(texId), true); // 텍스처 재설정
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);

	direction = { 0.f, 0.f };
	look = { 1.f, 0.f };

	shootTimer = 0.f;
	shootInterval = 0.1f; 

	hp = maxHp;		
	 
	 

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


	auto it = bulletList.begin(); // 총알 리스트를 순회하는 반복자, 불릿리스트에서 총알 하나씩 꺼내서 비활성화 되어 있으면 Pool에 집어넣고 리스트에서 삭제, 활성화 되어있으면 넘어감
	while (it != bulletList.end()) // 비활성화된 오브젝트를 없애는 대신 재활용하기 위해 따로 모아두는 것.
	{
		if (!(*it)->GetActive())
		{
			bulletPool.push_back(*it);
			it = bulletList.erase(it);
		}
		else
		{
			++it;
		}
	}


	sf::Vector2i mousePosition = InputMgr::GetMousePosition(); // 마우스 위치 가져오기
	sf::Vector2f mouseWorldPosition = sceneGame->ScreenToWorld(mousePosition); // 월드 좌표로 변환
	look = Utils::GetNormal(mouseWorldPosition - GetPosition()); // 플레이어가 바라보는 방향 계산
	SetRotation(Utils::Angle(look)); // 플레이어 회전 설정
	
	shootTimer += dt; // 슈팅 타이머 업데이트
	if(InputMgr::GetMouseButton(sf::Mouse::Left) && shootTimer>shootInterval)
	{
		Shoot();
		shootTimer = 0.f;	
	}

}


void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}


void Player::Shoot()
{
	Bullet* bullet = nullptr;
	if(bulletPool.empty()) // 총알이 없으면 새로 생성
	{
		bullet = new Bullet(); // 총알 객체 생성
		bullet->Init(); 
	}
	else // 총알이 있으면 풀에서 가져오기
	{
		bullet = bulletPool.front(); // 풀에서 첫 번째 총알 가져오기
		bulletPool.pop_front(); // 총알 풀에서 제거
		bullet->SetActive(true); // 총알 활성화
	}

	bullet->Reset();
	bullet->Fire(position + look * 10.f, look, 1000.f, 10);

	bulletList.push_back(bullet); // 총알 리스트에 추가
	sceneGame->AddGameObject(bullet);
}

void Player::OnDamage(int damage)
{
	if (!isAlive)
	{
		return;
	}

	hp = Utils::Clamp(hp - damage, 0, maxHp); 
	if (hp <= 0)
	{
		hp = 0;
		isAlive = false; // 플레이어가 죽었음을 표시
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}
