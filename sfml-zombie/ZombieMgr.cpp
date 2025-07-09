#include "stdafx.h"
#include "ZombieMgr.h"
#include "Zombie.h"
#include "Blood.h"
#include "TextGo.h"
void ZombieMgr::SpawnBlood(const sf::Transformable& trans)
{
	Blood* blood;
	if (bloodPool.empty()) {
		blood = new Blood();
		blood->Init();
	}
	else {
		blood = bloodPool.front();
		bloodPool.pop_front();
	}
	blood->Reset();
	blood->SetActive(true);
	blood->SetPosition(trans.getPosition());
	scene->AddGameObject(blood);
}
void ZombieMgr::Init()
{
	
}

void ZombieMgr::Update(float dt)
{
	std::list<Zombie*>::iterator iter = zombieList.begin();
	dieZombie = 0;
	while (iter != zombieList.end()) {
		if (!(*iter)->GetActive()) {
			SpawnBlood((*iter)->GetSprite());
			zombiePool.push_back(*iter);
			iter = zombieList.erase(iter);
			dieZombie++;
		}
		else {
			iter++;
		}
	}
	
	for (Zombie* zombie : zombieList) {
		zombie->Update(dt);


		//std::cout << zombie->GetPosition().x << ", " << zombie->GetPosition().y << std::endl;
	}
	
	if (InputMgr::GetKeyDown(sf::Keyboard::F)) {
		for (Zombie* zombie : zombieList) {
			zombie->OnDamage(1000000);
		}
	}
}

void ZombieMgr::Release()
{
	
}

void ZombieMgr::Enter()
{
	for (auto i : zombieList) {
		zombiePool.push_back(i);
	}
	zombieList.clear();
}

void ZombieMgr::SpawnZombie(int count , float radious)
 {
	for (int i = 0; i < count; i++) {
		Zombie* zombie;
		if (zombiePool.empty()) {
			zombie = new Zombie();
			zombie->Init();
			scene->AddGameObject(zombie);
			zombie->SetPlayer(player);
		}
		else {
			zombie = zombiePool.front();
			zombiePool.pop_front();
		}
		zombieList.push_back(zombie);
 		zombie->Reset();
		zombie->SetActive(true);
		zombie->SetPosition(Utils::RandomOnUnitCircle() * radious);
	}
}


void ZombieMgr::SettingScene(Scene* scene)
{
	this->scene = scene;
}

void ZombieMgr::SettingPlayer(Player* player) {
	this->player = player;
}
