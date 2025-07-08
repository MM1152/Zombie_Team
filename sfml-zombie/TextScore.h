#pragma once
#include "TextGo.h"
class TextScore : public TextGo
{
protected:
	int score;
	
public:
	TextScore(const std::string& fontId = "", const std::string& name = "");
	~TextScore() override = default;

	void Init() override;
	void Reset() override;
	void SetScore(int score);
};

