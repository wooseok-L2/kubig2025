#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data";

int main()
{
    Mat img(400, 600, CV_8UC3, white);

    int a = 0, b = 0, c = 0;

    while (true)
    {
        img.setTo(white); // 배경 그리기
        putText(img, "This is kuBig2025 test TEXT.", Point(20 + a, 50), FONT_HERSHEY_SIMPLEX, 2, red);
        putText(img, "This is kuBig2025 test TEXT.", Point(20 + a, 100), FONT_ITALIC, 2, red);
        putText(img, "This is kuBig2025 test TEXT.", Point(20 + a, 150), FONT_HERSHEY_DUPLEX, 3, blue);
        putText(img, "This is kuBig2025 test TEXT.", Point(20 + a, 200), FONT_HERSHEY_PLAIN, 4, black);

        imshow("img", img);
        if (waitKey(33) == 27)
            break;
        a += 1;
        b -= 1;
        c += 3;
    }
    destroyAllWindows();
    return 0;
}