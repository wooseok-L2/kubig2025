#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    Vec3b p1, p2(0, 0, 255);
    p1[0] = 100;
    cout << "p1 : " << p1 << endl;
    cout << "p2 : " << p2 << endl;

    Scalar gray = 128;
    cout << "gray : " << gray << endl;

    Scalar yellow(0, 255, 255);
    cout << "yellow : " << yellow << endl;

    return 0;
}