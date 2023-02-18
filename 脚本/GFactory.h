#pragma once
#include "Game.h"

class Game;
//����ģʽ
class GFactory{
public:
	virtual Game* CreateGame() = 0;
};

class CollapseFactory : public GFactory {
public:
	Game* CreateGame() final override;
};