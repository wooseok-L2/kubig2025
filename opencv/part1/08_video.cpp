#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    VideoCapture cap(folderPath + "vtest.avi");
    if (!cap.isOpened()){
        cerr << "no vedio file" << endl;
    }
    cout << "Frame width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
    cout << "Frame height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
    auto fps = cap.get(CAP_PROP_FPS);
    cout << "fps : " << cvRound(fps) << endl;

    Mat frame;

    while(true)
    {
        cap >> frame;
        if(frame.empty())
            break;   // quit after last frame

        imshow("frame", frame);

        if (waitKey(1000 / fps) == 27)   // 27 is ESC
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}