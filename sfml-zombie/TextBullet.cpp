#include "stdafx.h"
#include "TextBullet.h"

TextBullet::TextBullet(const std::string& name)
	: TextGo("fonts/zombiecontrol.ttf", name)
{
	texIds = "graphics/ammo_icon.png";	
}

void TextBullet::Init()
{
	TextGo::Init();

}

void TextBullet::Release()
{
	TextGo::Release();
}

void TextBullet::Reset()
{
	TextGo::Reset();
	SetPosition({ 100.f , FRAMEWORK.GetWindowSizeF().y - 100.f });
	SetOrigin(Origins::TL);

	bulletImg.setTexture(TEXTURE_MGR.Get(texIds));
	bulletImg.setPosition({ GetPosition().x - 50.f , GetPosition().y + 20.f});
	Utils::SetOrigin(bulletImg, Origins::ML);
}

void TextBullet::Update(float dt)
{
	TextGo::Update(dt);
}

void TextBullet::Draw(sf::RenderWindow& window)
{
	TextGo::Draw(window);
	window.draw(bulletImg);
}


void TextBullet::SetBulletCount(int curCount, int maxCount)
{
	SetString(std::to_string(curCount) + " / " + std::to_string(maxCount));
}



