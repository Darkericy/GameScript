#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

class ImgWork{
	ImgWork() = default;
	~ImgWork() = default;

    //��Ļ����
    BITMAPINFOHEADER createBitmapHeader(int width, int height);

	void captureScreenMat();

	//����������
	void leftClick(const pair<int, int>&);

	string gameSourceDir;

	const static double zra;
	const static double zoom;
	const static string ScreenShotDir;
	const static int method;
	const static string imageEnd;
public:
	static ImgWork* Instance();

	void changeGameDir(const string&);

	//�������Ƶ����Ӧͼ��
	void select(const string&);
};