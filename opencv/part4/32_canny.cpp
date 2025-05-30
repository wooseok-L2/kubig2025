#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/opencv.hpp>
// #include <thread>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    VideoCapture cap(0);
    Mat img, edge;
    int low_v, high_v;
    namedWindow("img1");
    createTrackbar("lowedge", "img1", &low_v, 255);
    createTrackbar("highedge", "img1", &high_v, 255);

    // vector img show 코드
    while (true)
    {
        cap >> img;
        Canny(img, edge, low_v, high_v);
        imshow("img1", edge);
        if (waitKey(33) == 27)
            break;
    }
    
    destroyAllWindows();
    return 0;
}
