#include <iostream>
#include <opencv2/opencv.hpp>
#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

void on_mouse(int event, int x, int y, int flags, void *data);

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
    namedWindow("img");
    Mat frame;
    Rect rec;
    setMouseCallback("img", on_mouse, (void *)&rec);

    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break; // 마지막 프레임 처리
        rectangle(frame, rec, red, 3, LINE_AA);
        cout << rec << endl;
        imshow("img", frame);
        if (waitKey(1000 / fps) == 27) // fps 조절 숫자.
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}

void on_mouse(int event, int x, int y, int flags, void *data)
{
    Rect *rect = (Rect *)data;
    static Point temp;
    switch (event)
    {
    case EVENT_LBUTTONDOWN:
        temp.x = x;
        temp.y = y;
        cout << "button down" << endl;
        break;
    case EVENT_LBUTTONUP:
        rect->x = temp.x;
        rect->y = temp.y;
        rect->width = x - temp.x;
        rect->height = y - temp.y;
        cout << "button up" << endl;
        break;
    case EVENT_MOUSEMOVE:
        break;
    default:
        // cout << "마우스 이벤트!!" << endl;
        break;
    }
}