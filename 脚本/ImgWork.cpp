#include "ImgWork.h"

const double ImgWork::zra = 1.255;
const double ImgWork::zoom = 1.51;
const string ImgWork::ScreenShotDir = "./temp/screenshot.jpg";
const int ImgWork::method = TM_CCOEFF_NORMED;
const string ImgWork::imageEnd = ".jpg";

ImgWork* ImgWork::Instance() {
    static ImgWork work;
    return &work;
}

BITMAPINFOHEADER ImgWork::createBitmapHeader(int width, int height) {
    BITMAPINFOHEADER  bi;

    // create a bitmap
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    return bi;
}

void ImgWork::captureScreenMat() {
    Mat src;
    HWND hwnd = GetDesktopWindow();

    // get handles to a device context (DC)
    HDC hwindowDC = GetDC(hwnd);
    HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    // define scale, height and width
    int screenx = GetSystemMetrics(SM_XVIRTUALSCREEN);
    int screeny = GetSystemMetrics(SM_YVIRTUALSCREEN);
    int width = GetSystemMetrics(SM_CXVIRTUALSCREEN) * zra;
    int height = GetSystemMetrics(SM_CYVIRTUALSCREEN) * zra;

    // create mat object
    src.create(height, width, CV_8UC4);

    // create a bitmap
    HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    BITMAPINFOHEADER bi = createBitmapHeader(width, height);

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);

    // copy from the window device context to the bitmap device context
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, screenx, screeny, width, height, SRCCOPY);  //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);            //copy from hwindowCompatibleDC to hbwindow

    // avoid memory leak
    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    cv::imwrite(ScreenShotDir, src);
}

void ImgWork::changeGameDir(const string& Dir) {
    gameSourceDir = "./source/";
    gameSourceDir += Dir;
    gameSourceDir += "/";
}

void ImgWork::leftClick(const pair<int, int>& pos) {
    SetCursorPos(pos.first, pos.second);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(10);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void ImgWork::select(const string& target) {
    captureScreenMat();
    Mat srcImage = imread("./temp/screenshot.jpg");  //原图
    Mat tempImage = imread(gameSourceDir + target + imageEnd); //模板图像

    Mat resultImage; //结果图像
    int resultImage_rows = srcImage.rows - tempImage.rows + 1;  //结果图像的行数：W-w+1，W：原图像的行数，w：模板图像的行数
    int resultImage_cols = srcImage.cols - tempImage.cols + 1;  //结果图像的列数：H-h+1，H：原图像的列数，h：模板图像的列数
    resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);   //结果图像必须为单通道32位浮点型

    //TM_SQDIFF:平方差匹配法  TM_SQDIFF_NORMED:归一化平方差匹配法  
    //TM_CCORR:相关匹配法 M_CCORR_NORMED:归一化相关匹配法  TM_CCOEFF:系数匹配法  TM_CCOEFF_NORMED:化相关系数匹配法
    matchTemplate(srcImage, tempImage, resultImage, method);    //模板匹配
    normalize(resultImage, resultImage, 0, 1, NORM_MINMAX, -1, Mat());  //归一化处理

    double minValue, maxValue;
    Point minLocation, maxLocation, matchLocation;

    minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat()); //在resultImage中矩阵的每一个点的亮度表示与模板T的匹配程度

    if (method == TM_SQDIFF || method == TM_SQDIFF_NORMED)  //越小越匹配
    {
        matchLocation = minLocation;    //匹配图像的左上角
    }
    else //越大越匹配
    {
        matchLocation = maxLocation;
    }

    //rectangle(srcImage, matchLocation, Point(matchLocation.x + tempImage.cols, matchLocation.y + tempImage.rows), Scalar(0, 0, 255), 2, 8, 0);
    //std::cout << "左上角坐标:" << matchLocation << std::endl;
    //std::cout << "右下角坐标：" << Point(matchLocation.x + tempImage.cols, matchLocation.y + tempImage.rows) << std::endl;
    ////输出图像
    //imwrite("./temp/图片.jpg", srcImage);

    int x = (matchLocation.x + tempImage.cols) / 2, y = (matchLocation.y + tempImage.rows) / 2;
    pair<int, int> pos = make_pair(x * zoom, y * zoom);
    leftClick(pos);
}