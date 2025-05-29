#include <iostream>
#include <opencv2/opencv.hpp>
#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    Mat img1 = imread(folderPath + "lenna.bmp");
    Mat img2 = imread(folderPath + "mask_smile.bmp", IMREAD_GRAYSCALE);    //gray scale image

    img1.setTo(yellow, img2);
    imshow("img", img1);

    Mat airplane = imread(folderPath + "airplane.bmp");
    Mat maskAirplane = imread(folderPath + "mask_plane.bmp", IMREAD_GRAYSCALE);
    Mat sky = imread(folderPath + "field.bmp");

    airplane.copyTo(sky, maskAirplane);
    imshow("sky", sky);

    waitKey();
    destroyAllWindows();

    return 0;
}