#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <unistd.h>
#include <zmq.hpp>

using namespace std;
using namespace zmq;
using namespace cv;
using namespace cv::dnn;

void on_mouse(int event, int x, int y, int flags, void *userdata);

int main()
{
    context_t context(1);
    socket_t requester(context, socket_type::req);
    const char *ipc_file_path = "/tmp/zmq_server";
    requester.connect("ipc://" + string(ipc_file_path));
    cout << "클라이언트가 IPC 소켓에 연결되었습니다: " << ipc_file_path << endl;
    int request_count = 0;
    Mat img = Mat::zeros(400, 400, CV_8UC1);
    imshow("img", img);
    setMouseCallback("img", on_mouse, (void *)&img);
    waitKey(1000);
    while (true)
    {
        int c = waitKey(30);
        if (c == 27)
        {
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else if (c == ' ')
        {
            recv_result_t result = requester.send(zmq::buffer(img.data, img.total() * img.elemSize()), send_flags::none);
            message_t reply_msg;
            recv_result_t reply_result = requester.recv(reply_msg, recv_flags::none);
            cout << "그린 숫자의 번호는 " << reply_msg.to_string() << "입니다." << endl;
            img.setTo(0);
            imshow("img", img);
        }
    }
    return 0;
}

void on_mouse(int event, int x, int y, int flags, void *userdata)
{
    Mat &img = *(Mat *)userdata;
    static Point ptPrev = Point(-1, -1);
    static bool isDrawing = false;
    if (event == EVENT_LBUTTONDOWN)
    {
        ptPrev = Point(x, y);
        isDrawing = true;
    }
    else if (event == EVENT_LBUTTONUP)
    {
        ptPrev = Point(-1, -1);
        isDrawing = false;
    }
    else if (event == EVENT_MOUSEMOVE && ptPrev.x >= 0 && ptPrev.y >= 0 && isDrawing)
    {
        line(img, ptPrev, Point(x, y), Scalar(255), 30, LINE_AA, 0);
        ptPrev = Point(x, y);
        imshow("img", img);
    }
}