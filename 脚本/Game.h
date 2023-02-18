#pragma once
#include <iostream>
#include <conio.h>
#include "ImgWork.h"
using namespace std;

class Game{
public:
	virtual ~Game() = default;
	Game() = default;
	Game(const Game& lhs) = delete;
	Game& operator= (const Game& lhs) = delete;

	virtual void begin() = 0;
	virtual void end() = 0;
};

class collapse_three : public Game {
public:
	void begin() final override;

	void end() final override;
};
