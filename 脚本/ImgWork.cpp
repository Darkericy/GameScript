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

bool ImgWork::can_select(const string& target, pair<int, int>& pos) {
    captureScreenMat();

    Mat srcImage = imread("./temp/screenshot.jpg");  //ԭͼ
    Mat tempImage = imread(gameSourceDir + target + imageEnd); //ģ��ͼ��

    Mat resultImage; //���ͼ��
    int resultImage_rows = srcImage.rows - tempImage.rows + 1;  //���ͼ���������W-w+1��W��ԭͼ���������w��ģ��ͼ�������
    int resultImage_cols = srcImage.cols - tempImage.cols + 1;  //���ͼ���������H-h+1��H��ԭͼ���������h��ģ��ͼ�������
    resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);   //���ͼ�����Ϊ��ͨ��32λ������

    //TM_SQDIFF:ƽ����ƥ�䷨  TM_SQDIFF_NORMED:��һ��ƽ����ƥ�䷨  
    //TM_CCORR:���ƥ�䷨ M_CCORR_NORMED:��һ�����ƥ�䷨  TM_CCOEFF:ϵ��ƥ�䷨  TM_CCOEFF_NORMED:�����ϵ��ƥ�䷨
    matchTemplate(srcImage, tempImage, resultImage, method);    //ģ��ƥ��
    //normalize(resultImage, resultImage, 0, 1, NORM_MINMAX, -1, Mat());  //��һ������

    double minValue, maxValue;
    Point minLocation, maxLocation, matchLocation;

    minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat()); //��resultImage�о����ÿһ��������ȱ�ʾ��ģ��T��ƥ��̶�

    if (maxValue < 0.9) {
        return false;
    }

    matchLocation = maxLocation;
    int x = (matchLocation.x + tempImage.cols) / 2, y = (matchLocation.y + tempImage.rows) / 2;
    pos = make_pair(x * zoom, y * zoom);
    return true;
}