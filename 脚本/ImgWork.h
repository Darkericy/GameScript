#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

class ImgWork{
	ImgWork() = default;
	~ImgWork() = default;

    //屏幕截屏
    BITMAPINFOHEADER createBitmapHeader(int width, int height);

	void captureScreenMat();

	//鼠标左键单击
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

	//按照名称点击对应图标
	void select(const string&);
};