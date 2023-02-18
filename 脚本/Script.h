#pragma once
#include <iostream>
#include "GFactory.h"
using namespace std;

class Script {
	bool is_end;

	void ShowMenu();

public:
	Script() : is_end(false) {};
	~Script() = default;
	Script& operator= (const Script& lhs) = delete;
	Script(const Script& lhs) = delete;

	void start();
};