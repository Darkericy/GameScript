#pragma once
#include <iostream>
class Game{
public:
	virtual ~Game() = default;
	Game() = default;
	Game(const Game& lhs) = delete;
	Game& operator= (const Game& lhs) = delete;

	virtual void begin() = 0;
};

class collapse_three : public Game {
public:
	void begin() final override;
};
