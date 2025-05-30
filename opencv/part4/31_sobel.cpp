#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/opencv.hpp>
// #include <thread>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "lenna.bmp", IMREAD_GRAYSCALE);
    vector<Mat> images;

    Mat dx, dy;
    Sobel(img, dx, CV_32FC1, 1, 0);   //기울기 계산
    Sobel(img, dy, CV_32FC1, 0, 1);

    Mat magni, phase_mat;
    magnitude(dx, dy, magni);   // 기울기 강도 계산
    phase(dx, dy, phase_mat, true);   // 기울기 방향 계산
    
    dx.convertTo(dx, CV_8UC1);
    images.push_back(dx);
    dy.convertTo(dy, CV_8UC1);
    images.push_back(dy);
    magni.convertTo(magni, CV_8UC1);
    images.push_back(magni);
    phase_mat.convertTo(phase_mat, CV_8UC1);
    images.push_back(phase_mat);
    Mat edge = magni > 150;
    images.push_back(edge);

    int i = 1;
    for (auto img : images)
    {
        imshow("img" + to_string(i), img);
        ++i;
    }
    
    waitKey();
    destroyAllWindows();
    return 0;
}
