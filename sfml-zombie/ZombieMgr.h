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
	Scene* scene = nullptr;
	Player* player = nullptr;
	int dieZombie = 0;

	void SpawnBlood(const sf::Transformable& trans);

public:
	void Init();
	void Update(float dt);
	void Release();
	void Enter();

	int GetDieZombieCount() const { return dieZombie; };
	void SpawnZombie(int count , float radious);
	void SettingScene(Scene* scene);
	void SettingPlayer(Player* player);
	std::list<Zombie*>& GetZombieList() { return zombieList; };
	


};

#define ZOMBIE_MGR ZombieMgr::Instance()
