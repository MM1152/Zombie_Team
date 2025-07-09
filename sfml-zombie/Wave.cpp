#include "stdafx.h"
#include "Wave.h"

Wave::Wave(const std::string& fontId, const std::string& name)
	:TextGo("fonts/zombiecontrol.ttf" , name)
{
}

void Wave::SetZombieCount(int count)
{
	zombieCount.setString("ZOMBIE : " + std::to_string(count));
	Utils::SetOrigin(zombieCount, originZombieCount);
}

void Wave::SetWaveString(int wave)
{
	SetString("WAVE : " + std::to_string(wave));
}

void Wave::Reset()
{
	zombieCount.setFont(FONT_MGR.Get(fontId));
	originZombieCount = Origins::TL;
	TextGo::Reset();
}

void Wave::Draw(sf::RenderWindow& window)
{
	TextGo::Draw(window);
	window.draw(zombieCount);
}

void Wave::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	text.setPosition(pos);
	zombieCount.setPosition({ GetPosition().x + 200.f , GetPosition().y });
}
