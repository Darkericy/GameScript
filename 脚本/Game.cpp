#include "Game.h"
collapse_three::collapse_three() {
	work = ImgWork::Instance();
}

void collapse_three::begin() {
	system("cls");
	while(!FindWindowA(nullptr, "����3")) {
		cout << "û�м�⵽������������������ȷ��" << endl;
		cout << "�����������" << endl;
		while (1) {
			if (_kbhit()) {
				_getch();
				break;
			}
		}
	}

	system("cls");
	cout << "�������ճ����������������5����������" << endl;
	int temp = 5;
	while (temp--) {
		cout << temp << endl;
		Sleep(1000);
	}
	work->changeGameDir("collapse_three");
	work->can_select("start");
	cout << "������" << endl;

}

void collapse_three::end() {
	cout << "�������ű��ѽ���,��������ص��˵�" << endl;
	while (true) {
		if (_kbhit()) {
			_getch();
			break;
		}
	}
	system("cls");
}
