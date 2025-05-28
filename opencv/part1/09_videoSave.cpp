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
    int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
    int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
    auto fps = cap.get(CAP_PROP_FPS);
    int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');

    VideoWriter outputVideo(folderPath + "inverse_vtest.avi", fourcc, fps, Size(w, h));
    if (!outputVideo.isOpened()){
        cerr << "fail to file producing" << endl;
        return -1;
    }

    Mat frame;

    while(true)
    {
        cap >> frame;
        frame = ~frame;     // color reverse
        if(frame.empty())
            break;   // quit after last frame

        outputVideo << frame;
        imshow("frame", frame);

        if (waitKey(1000 / fps) == 27)   // 27 is ESC
            break;
    }

    cap.release();
    outputVideo.release();
    destroyAllWindows();

    return 0;
}