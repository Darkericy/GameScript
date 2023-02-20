#pragma once
#include <memory>
#include "Game.h"

using namespace std;

class Game;
//����ģʽ
class GFactory{
public:
	virtual shared_ptr<Game> CreateGame() = 0;
};

class CollapseFactory : public GFactory {
public:
	shared_ptr<Game> CreateGame() final override;
};