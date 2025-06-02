#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "starfish.jpg", IMREAD_GRAYSCALE);
    vector<Mat> images;
    images.push_back(img);
    Size winSize(64, 128);

    HOGDescriptor hog(
        winSize,
        Size(16, 16),
        Size(8, 8),
        Size(8, 8),
        9);
    cout
        << "WinSize: " << hog.winSize << endl;

    vector<float> descriptors;
    if ((img.cols - hog.winSize.width) % hog.blockStride.width || (img.rows - hog.winSize.height) % hog.blockStride.height)
    {
        resize(img, img, Size(img.cols / hog.blockStride.width * hog.blockStride.width + hog.winSize.width, img.rows / hog.blockStride.height * hog.blockStride.height + hog.winSize.height));
    }
    cout << img.cols % hog.winSize.width << img.rows % hog.winSize.height;
    cout << img.cols << img.rows;
    cout << hog.blockStride.width;
    cout << hog.blockStride.height;

    hog.compute(img, descriptors);

    cout << "Hog 깊이" << descriptors.size() << endl;
    // SVM 학습 -> svm

    // hog.setSVMDetector(descriptors_svm);
    // vector<Rect> starfishes;
    // hog.detectMultiScale(img, starfishes);
    // cout << starfishes.size() << endl;

    // vector img show 코드
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