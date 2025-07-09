#pragma once
class HealItem : public GameObject
{
protected:
	int healAmount = 100; 

	bool isActive = false; 

public:
	HealItem();

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

