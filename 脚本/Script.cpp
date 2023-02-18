#include "Script.h"

void Script::ShowMenu() {
	printf_s("-------------------------------------\n");
	printf_s("|      MiHoYo全家桶日常脚本         |\n");
	printf_s("-------------------------------------\n");
	printf_s("|      请选择                       |\n");
	printf_s("|      1. 崩坏3                     |\n");
	printf_s("|      2. 退出                      |\n");
	printf_s("-------------------------------------\n");
}

void Script::start() {
	ShowMenu();
	int n;
	cin >> n;
	GFactory* factory = nullptr;
	while (!is_end) {
		switch (n) {
		case 1: {
			factory = new CollapseFactory();
			auto game = factory->CreateGame();
			game->begin();
			ShowMenu();
		}
		case 2:
			is_end = true;
		default: {
			cout << "请输入正确的数字。";
			ShowMenu();
		}
		}
	}
}
