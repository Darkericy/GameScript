#include "Game.h"
collapse_three::collapse_three() {
	work = ImgWork::Instance();
}

void collapse_three::begin() {
	system("cls");
	while(!FindWindowA(nullptr, "崩坏3")) {
		cout << "没有检测到崩坏三程序启动，请确认" << endl;
		cout << "按任意键继续" << endl;
		while (1) {
			if (_kbhit()) {
				_getch();
				break;
			}
		}
	}

	system("cls");
	cout << "崩坏三日常清理程序已启动，5秒后程序启动" << endl;
	int temp = 5;
	while (temp--) {
		cout << temp << endl;
		Sleep(1000);
	}
	work->changeGameDir("collapse_three");
	work->can_select("start");
	cout << "已启动" << endl;

}

void collapse_three::end() {
	cout << "崩坏三脚本已结束,按任意键回到菜单" << endl;
	while (true) {
		if (_kbhit()) {
			_getch();
			break;
		}
	}
	system("cls");
}
