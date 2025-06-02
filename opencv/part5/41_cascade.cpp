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
    Mat img = imread(folderPath + "kids.png");
    vector<Mat> images;
    images.push_back(img);
    images.emplace_back(img.clone());

    CascadeClassifier classifier(folderPath + "haarcascade_frontalface_default.xml");

    vector<Rect> faces;
    classifier.detectMultiScale(img, faces);

    for (auto &rect : faces)
    {
        rectangle(img, rect, red, 2);
    }
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