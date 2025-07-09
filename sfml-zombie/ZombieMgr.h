#pragma once
#include "stdafx.h"

class Zombie;
class Blood;
class TextGo;
class Player;
class ZombieMgr : public Singleton<ZombieMgr>
{
	friend Singleton<ZombieMgr>;
protected:
	ZombieMgr() = default;
	~ZombieMgr() = default;
	
	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;
	
	std::list<Blood*> bloodList;
	std::list<Blood*> bloodPool;
	Scene* scene;
	Player* player;
	int dieZombie = 0;

	void SpawnBlood(const sf::Transformable& trans);

public:
	void Init();
	void Update(float dt);
	void Release();
	void Enter();

	int GetDieZombieCount() const { return dieZombie; };
	void SpawnZombie(int count);
	void SettingScene(Scene* scene);
	void SettingPlayer(Player* player);
};

#define ZOMBIE_MGR ZombieMgr::Instance()
