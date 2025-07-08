#include "stdafx.h"
#include "Blood.h"

Blood::Blood(const std::string& name)
	:GameObject(name)
{
}

void Blood::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(pos);
}

void Blood::SetRotation(float rot)
{
	rotation = rot;
	body.setRotation(rot);
}

void Blood::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(s);
}

void Blood::SetOrigin(const sf::Vector2f& o)
{
	origin = o;
	originPreset = Origins::Custom;
	body.setOrigin(o);
}

void Blood::SetOrigin(Origins preset)
{
	originPreset = preset;
	Utils::SetOrigin(body, preset);
}

void Blood::Init()
{
	texId = "graphics/blood.png";
	
	SetPosition({ 0.f , 0.f });
	SetScale({ 1.f , 1.f });
	SetOrigin(Origins::MC);
}

void Blood::Release()
{
}

void Blood::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	initColor = body.getColor();
	curColor = body.getColor();
}

void Blood::Update(float dt)
{
	if (GetActive()) {
		timer += dt * speed;
		if (timer >= 1) {
			curColor = body.getColor();
			curColor.a -= timer;
			timer = 0;

			body.setColor(curColor);
		}
		
		if (curColor.a <= 0) {
			SetActive(false);
			body.setColor(initColor);
		}
	}
	
}

void Blood::Draw(sf::RenderWindow& window)
{
	if (GetActive()) {
		window.draw(body);
	}
}
