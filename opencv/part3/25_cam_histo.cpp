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

    Mat lenna = imread(folderPath + "lenna256.bmp", IMREAD_GRAYSCALE);
    resize(lenna, lenna, Size(cvRound(cap.get(CAP_PROP_FRAME_WIDTH)), cvRound(cap.get(CAP_PROP_FRAME_HEIGHT))));

    Mat frame;
    Mat gray_frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break; // 마지막 프레임 처리
        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
        equalizeHist(gray_frame, gray_frame);
        addWeighted(gray_frame, 0.5, lenna, 0.5, 0, gray_frame);

        imshow("frame", gray_frame);
        imshow("frame2", frame);
        if (waitKey(1000 / fps) == 27) // fps 조절 숫자.
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}