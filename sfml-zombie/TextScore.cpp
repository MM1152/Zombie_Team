#include "stdafx.h"
#include "TextScore.h"

TextScore::TextScore(const std::string& fontId, const std::string& name)
	:TextGo("fonts/zombiecontrol.ttf" , name)
{
}

void TextScore::Init()
{
	TextGo::Init();
}

void TextScore::Reset()
{
	TextGo::Reset();

	score = 0;
	SetScore(0);
	SetOrigin(Origins::MC);
}

void TextScore::SetScore(int score)
{
	this->score += score;
	SetString("Score : " + std::to_string(this->score));
}
