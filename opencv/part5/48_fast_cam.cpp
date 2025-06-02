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
    VideoCapture cap(0);
    Ptr<Feature2D> feature = ORB::create();
    vector<KeyPoint> keypoints;
    vector<Point2f> corners;
    Mat img, img1, img2, gray_img, desc;
    while (true)
    {
        cap >> img;
        img1 = img.clone();
        img2 = img.clone();

        // FAST
        cvtColor(img, gray_img, COLOR_BGR2GRAY);
        FAST(gray_img, keypoints, 60, true);
        for (auto &k : keypoints)
        {
            circle(img, Point(cvRound(k.pt.x), cvRound(k.pt.y)), 5, red, 2);
        }
        imshow("img", img);

        // goodFeature
        goodFeaturesToTrack(gray_img, corners, 1000, 0.01, 10);
        for (auto &p : corners)
        {
            circle(img1, Point(p.x, p.y), 5, red, 2);
        }
        imshow("img1", img1);

        // ORB
        // feature->detect(img, keypoints);
        // feature->compute(img, keypoints, dst);
        feature->detectAndCompute(img2, noArray(), keypoints, desc);
        drawKeypoints(img2, keypoints, img2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        imshow("img2", img2);
        if (waitKey(33) == 27)
            break;
    }
    
    destroyAllWindows();
    return 0;
}