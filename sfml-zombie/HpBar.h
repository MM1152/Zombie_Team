#pragma once
#include "GameObject.h"
class HpBar :
    public GameObject
{
protected:
	sf::RectangleShape rect;
	sf::Vector2f initSize;
	//TODO : �÷��̿� ���� �ʿ�
public:
	HpBar(const std::string& name = "");
	virtual ~HpBar() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SettingHp(int hp , int maxHp);
};

