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
      Mat img = imread(folderPath + "lenna.bmp");
    vector<Mat> images;

    // image 추가
    images.push_back(img.clone());
    for (int i = 0; i < 3; ++i)
        images.emplace_back(Mat());

    // 이동 변환
    Mat M = Mat_<double>({2, 3}, {1, 0, 150, 0, 1, 100});
    // [ 1, 0 , 150]
    // [ 0, 1 , 100]
    warpAffine(img, images[1], M, img.size() + Size(150, 100));

    // 전단 변환
    double mx = 0.3, my = 0.2;
    M = Mat_<double>({2, 3}, {1, mx, 0, my, 1, 0});
    warpAffine(img, images[2], M, Size());

    // 어파인 변환
    Point2f srcPts[3], dstPts[3];
    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(1, 0);
    srcPts[2] = Point2f(1, 1);
    dstPts[0] = Point2f(0, 0);
    dstPts[1] = Point2f(2, 1);
    dstPts[2] = Point2f(1.5, 1.3);
    M = getAffineTransform(srcPts, dstPts);
    warpAffine(img, images[3], M, img.size() + Size(500, 500));

   // vector img show code
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