#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/opencv.hpp>
// #include <thread>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

typedef struct
{
    int lower_hue;
    int upper_hue;
} Mydata;

void on_hue_changed(int pos, void *data);

int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cerr << "동영상 파일이 없습니다!" << endl;
    }
    
    Mydata mydata;
    Mat bil_frame, frame;

    createTrackbar("lower Hue", "img2", &mydata.lower_hue, 179, on_hue_changed, (void *)&mydata);
    createTrackbar("upper Hue", "img2", &mydata.upper_hue, 179, on_hue_changed, (void *)&mydata);

    // vector img show 코드
    while (true)
    {
        cap >> frame;
        if(frame.empty())
            break;

        bil_frame = frame.clone();
        bilateralFilter(bil_frame, bil_frame, -1, 10, 5);

        imshow("frame", bil_frame);
        if (waitKey(33) == 27)
            break;
    }
    
    destroyAllWindows();
    return 0;
}

void on_hue_changed(int pos, void *data)
{
    Mydata *mydata = (Mydata *)data;
    Scalar lowerb(mydata->lower_hue, 0, 0);
    Scalar upperb(mydata->upper_hue, 255, 255);
    inRange(mydata->images[0], lowerb, upperb, mydata->images[1]);
    imshow("img2", mydata->images[1]);
}