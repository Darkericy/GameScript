#pragma once
#include "Game.h"

class Game;
//工厂模式
class GFactory{
public:
	virtual Game* CreateGame() = 0;
};

class CollapseFactory : public GFactory {
public:
	Game* CreateGame() final override;
};