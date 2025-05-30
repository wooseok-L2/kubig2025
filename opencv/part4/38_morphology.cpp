#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/opencv.hpp>
// #include <thread>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

typedef struct
{
    int lower_hue;
    int upper_hue;
    vector<Mat> images;
} Mydata;

void on_hue_changed(int pos, void *data);

int main()
{
    Mat img = imread(folderPath + "milkdrop.bmp", IMREAD_GRAYSCALE);
    vector<Mat> images;
    images.push_back(img);
    for (int i = 0; i < 5; ++i)
        images.emplace_back(Mat());
    threshold(img, images[1], 0, 255, THRESH_BINARY | THRESH_OTSU);
    erode(images[1], images[2], Mat());
    dilate(images[1], images[3], Mat());
    morphologyEx(images[1], images[4], MORPH_OPEN, Mat(), Point(-1, -1), 4);
    morphologyEx(images[4], images[5], MORPH_CLOSE, Mat(), Point(-1, -1), 3);

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

void on_hue_changed(int pos, void *data)
{
    Mydata *mydata = (Mydata *)data;
    Scalar lowerb(mydata->lower_hue, 0, 0);
    Scalar upperb(mydata->upper_hue, 255, 255);
    inRange(mydata->images[0], lowerb, upperb, mydata->images[1]);
    imshow("img2", mydata->images[1]);
}