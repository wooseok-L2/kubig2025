#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "lenna.bmp", IMREAD_GRAYSCALE);
    vector<Mat> images;
    images.push_back(img.clone());

    int num = (int)(img.total() * 0.1);
    for (int i = 0; i < num; i++){
        int x = rand() % img.cols;
        int y = rand() % img.rows;
        img.at<uchar>(y, x) = (i % 2) * 255;
    }
    
    images.push_back(img);

    for(int i = 0; i < 3; i++){
        images.emplace_back(Mat());
    }

    GaussianBlur(img, images[2], Size(), 5);
    bilateralFilter(img, images[3], -1, 10, 5);
    medianBlur(img, images[4], 5);

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