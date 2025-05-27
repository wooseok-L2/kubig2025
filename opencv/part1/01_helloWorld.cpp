#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    cout << "hello, world" << endl;

    Mat img = imread(folderPath + "lenna.bmp");

    if(img.empty())
    {
        cerr << "Fail to take images";

        return -1;
    }

    // cout << "img" << endl;

    namedWindow("lenna", WINDOW_NORMAL);
    setWindowProperty("lenna", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
    // Size size(640, 480);
    // resizeWindow("lenna", size);

    imshow("lenna", img);
    waitKey();
    vector<int> jpg_params;
    jpg_params.push_back(IMWRITE_JPEG_QUALITY);
    jpg_params.push_back(20);

    imwrite(folderPath + "lenna_save_20.jpg", img, jpg_params);

    return 0;
}