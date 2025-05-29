#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

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

    Mat frame;
    Mat filter_frame, rc_frame;

    float data[] = {-1, -1, 0, -1, 0, 1, 0, 1, 1};
    Mat emboss(3, 3, CV_32FC1, data);
    Rect rc(500, 100, 500, 500);
    float alpha = 3.f;

    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break; // 마지막 프레임 처리
        // cvtColor(frame, frame, COLOR_BGR2GRAY);
        // filter2D(frame, filter_frame, -1, emboss, Point(-1, -1), 0, BORDER_REPLICATE);
        rc_frame = frame(rc);
        // blur(filter_frame, filter_frame, Size(15, 15), Point(-1, -1), BORDER_REPLICATE);
        // shapening
        // GaussianBlur(rc_frame, filter_frame, Size(0, 0), 7);
        // filter_frame = (1 + alpha) * rc_frame - alpha * filter_frame;
        // filter_frame.copyTo(rc_frame);
        // bilateral
        bilateralFilter(rc_frame, filter_frame, -1, 10, 10);

        imshow("frame", filter_frame);
        imshow("frame_org", frame);
        if (waitKey(1000 / fps) == 27) // fps 조절 숫자.
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}