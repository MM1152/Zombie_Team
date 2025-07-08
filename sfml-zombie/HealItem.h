#pragma once
class HealItem : public GameObject
{
protected:
	int healAmount = 100; 

	bool isActive = false; 

public:
	HealItem();

	// GameObject��(��) ���� ��ӵ�
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

