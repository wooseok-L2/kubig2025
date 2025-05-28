#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    VideoCapture cap(folderPath + "vtest.avi");
    Mat frame;

    while(true)
    {
        cap >> frame;
        imshow("frame", frame);
        if (waitKey(33) == 27)   // 27 is ESC
            break;
    }

    return 0;
}