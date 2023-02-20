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
	GFactory* factory = nullptr;
	int n;
	while (!is_end) {
		ShowMenu();
		cin >> n;
		switch (n) {
		case 1: {
			factory = new CollapseFactory();
			auto game = factory->CreateGame();
			game->begin();
			game->end();
			break;
		}
		case 2:
			is_end = true;
			break;

		default: {
			cout << "��������ȷ�����֡�";
			ShowMenu();
			break;
		}
		}
	}
}
