#include "Script.h"

void Script::ShowMenu() {
	printf_s("-------------------------------------\n");
	printf_s("|      MiHoYoȫ��Ͱ�ճ��ű�         |\n");
	printf_s("-------------------------------------\n");
	printf_s("|      ��ѡ��                       |\n");
	printf_s("|      1. ����3                     |\n");
	printf_s("|      2. �˳�                      |\n");
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
			cout << "��������ȷ�����֡�";
			ShowMenu();
		}
		}
	}
}
