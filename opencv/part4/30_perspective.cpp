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
    Point2f srcPts[4];
    Point2f dstPts[4];
    Mat frame;
    Mat dst;
} Mydata;

void on_mouse(int event, int x, int y, int flags, void *userdata);

int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cerr << "동영상 파일이 없습니다!" << endl;
    }
    cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
    cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
    auto fps = cap.get(CAP_PROP_FPS);
    cout << "fps : " << cvRound(fps) << endl;

    namedWindow("frame");
    Mydata userdata;
    setMouseCallback("frame", on_mouse, (void *)&userdata);

    Mat frame;
    while (true)
    {
        cap >> userdata.frame;
        if (userdata.frame.empty())
            break; // 마지막 프레임 처리
        for (int i = 0; i < 4; ++i)
        {
            circle(userdata.frame, Point(userdata.srcPts[i].x, userdata.srcPts[i].y), 5, red, -1);
        }
        imshow("frame", userdata.frame);
        if (waitKey(1000 / fps) == 27) // fps 조절 숫자.
            break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}

void on_mouse(int event, int x, int y, int flags, void *userdata)
{
    Mydata *mydata = (Mydata *)userdata;
    static int cnt = 0;
    if (event == EVENT_LBUTTONDOWN)
    {
        if (cnt < 4)
        {
            mydata->srcPts[cnt++] = Point2f(x, y);
        }
        if (cnt == 4)
        {
            int w = 200, h = 300;
            mydata->dstPts[0] = Point2f(0, 0);
            mydata->dstPts[1] = Point2f(w - 1, 0);
            mydata->dstPts[2] = Point2f(w - 1, h - 1);
            mydata->dstPts[3] = Point2f(0, h - 1);
            Mat M = getPerspectiveTransform(mydata->srcPts, mydata->dstPts);
            warpPerspective(mydata->frame, mydata->dst, M, Size(w, h));
            imshow("dst", mydata->dst);
            cnt = 0;
        }
    }
}