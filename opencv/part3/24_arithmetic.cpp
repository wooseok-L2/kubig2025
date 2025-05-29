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
    Mat img = imread(folderPath + "lenna256.bmp", IMREAD_GRAYSCALE);
    Mat img2 = imread(folderPath + "square.bmp", IMREAD_GRAYSCALE);
    
    namedWindow("img");
    vector<Mat> images;
    images.push_back(img);
    images.push_back(img2);

    Mat dst1, dst2, dst3, dst4;
    add(img, img2, dst1);
    addWeighted(img, 0.5, img2, 0.5, 0, dst2);
    subtract(img, img2, dst3);
    absdiff(img, img2, dst4);
    images.push_back(dst1);
    images.push_back(dst2);
    images.push_back(dst3);
    images.push_back(dst4);

    int i = 1;
    for (auto img : images)
    { 
        imshow("img" + to_string(i), img);
        i++;
    }

    waitKey();
    destroyAllWindows();
    return 0;
}