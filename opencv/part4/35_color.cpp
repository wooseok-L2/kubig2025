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
    Mat img = imread(folderPath + "candies.png");
    vector<Mat> images;
    images.push_back(img);
    vector<Mat> bgr_planes, b_planes, g_planes, r_planes;
    split(img, bgr_planes);
    Mat empty(img.rows, img.cols, CV_8UC1, Scalar(0));
    b_planes = {bgr_planes[0], empty, empty};
    g_planes = {empty, bgr_planes[1], empty};
    r_planes = {empty, empty, bgr_planes[2]};
    Mat b_merge, g_merge, r_merge;

    merge(b_planes, b_merge);
    merge(g_planes, g_merge);
    merge(r_planes, r_merge);

    images.push_back(b_merge);
    images.push_back(g_merge);
    images.push_back(r_merge);

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
