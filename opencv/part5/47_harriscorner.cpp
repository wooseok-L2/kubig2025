#include <opencv2/aruco.hpp>
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
    Mat img = imread(folderPath + "building.jpg", IMREAD_GRAYSCALE);
    vector<Mat> images;
    images.push_back(img);
    Mat harris, harris_norm;
    cornerHarris(img, harris, 3, 3, 0.04);
    cout << harris.type() << endl;
    normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U);
    images.push_back(harris_norm);
    for (int j = 1; j < harris.rows - 1; j++)
    {
        for (int i = 1; i < harris.cols - 1; ++i)
        {
            if (harris_norm.at<uchar>(j, i) > 120)
            {
                circle(img, Point(i, j), 5, white, 2);
            }
        }
    }

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