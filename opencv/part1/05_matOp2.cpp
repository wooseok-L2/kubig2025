#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    Mat img(Size(600, 800), CV_8UC3);
    img.setTo(Scalar(0, 255, 0));
    Rect roi(220, 120, 200, 200);
    Mat img2 = img(roi);
    Mat img3 = img2.clone();

    img2.setTo(Scalar(0, 0, 255));
    img3.setTo(Scalar(0, 0, 0));

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            img.at<uint8_t>(220 + i, 120 + j) = (255, 255, 255);
        }
    }

    cout << img3.dims << " " << img3.rows << " "  << img3.cols<< " "  << img3.size() << " "  << img3.type() << " " << img3.depth()<< endl;
    cout << img3.elemSize() << endl;

    // imshow("img", img);
    imshow("img", img);
    imshow("img2", img2);
    imshow("img3", img3);
    waitKey();
    return 0;
}