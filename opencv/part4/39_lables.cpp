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
    // Mat img = imread(folderPath + "neutrophils.png", IMREAD_GRAYSCALE);
    Mat img = imread(folderPath + "milkdrop.bmp", IMREAD_GRAYSCALE);
    vector<Mat> images;
    images.push_back(img);
    for(int i = 0; i < 5; i++)
        images.emplace_back(Mat());
    threshold(img, images[1], 0, 255, THRESH_BINARY | THRESH_OTSU);
    erode(images[1], images[2], Mat());
    dilate(images[1], images[3], Mat());
    morphologyEx(images[1], images[4], MORPH_OPEN, Mat(), Point(-1, -1), 4);
    morphologyEx(images[1], images[5], MORPH_CLOSE, Mat(), Point(-1, -1), 3);

    Mat labels;
    int cnt = connectedComponents(images[3], labels);

    cout << "labels : \n" << labels << endl;
    cout << "number if labels : " << cnt << endl;

    Mat stats, centroids;
    cnt = connectedComponentsWithStats(images[3], labels, stats, centroids);

    for (int i = 1; i < cnt; i++){
        int *p = stats.ptr<int>(i);
        if (p[4] < 20)
            continue;
        rectangle(images[3], Rect(p[0], p[1], p[2], p[3]), Scalar(255));
        circle(images[3], Point(centroids.ptr<int>(i)[0], centroids.ptr<int>(i)[1]), 5, Scalar(255), -1);
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

