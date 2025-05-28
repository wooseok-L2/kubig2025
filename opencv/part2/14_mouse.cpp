#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";
void on_mouse(int event, int x, int y, int flags, void *data);

int main()
{
     Mat img = imread(folderPath + "lenna.bmp");
    namedWindow("img");

    setMouseCallback("img", on_mouse, (void *)&img);
    auto i = getTickCount();
    int keycode;
    while (true)
    {
        // cout << "keycode: " << keycode << endl;
        // cout << "i: " << i << endl;
        // cout << "fps: " << getTickFrequency() / (getTickCount() - i) << endl;
        i = getTickCount();
        imshow("img", img);
        keycode = waitKey(33);
        if (keycode == 27)
            break;
    }
}

void on_mouse(int event, int x, int y, int flags, void *data)
{
    static Point ptOld;
    static bool pushed;
    Mat *img = (Mat *)data;
    switch (event)
    {
    case EVENT_LBUTTONDOWN:
        ptOld = Point(x, y);
        pushed = true;
        break;
    case EVENT_LBUTTONUP:
        pushed = false;
        break;
    case EVENT_MOUSEMOVE:
        if (pushed)
        {
            line(*img, ptOld, Point(x, y), red, 2);
            ptOld = Point(x, y);
        }
        break;
    default:
        // cout << "마우스 이벤트!!" << endl;
        break;
    }
}