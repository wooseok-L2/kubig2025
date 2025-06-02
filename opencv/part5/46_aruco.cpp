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
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);

    vector<int> markerIds;
    vector<Vec3d> rvecs, tvecs;
    vector<vector<Point2f>> markerCorners;
    Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 640, 0, 1000, 360, 0, 0, 1);
    Mat distCoeffs = (Mat_<double>(5, 1) << 0, 0, 0, 0, 0);

    Mat img;
    while (true)
    {
        cap >> img;
        if (img.empty())
            break;
        aruco::detectMarkers(img, dictionary, markerCorners, markerIds);

        aruco::drawDetectedMarkers(img, markerCorners, markerIds);

        aruco::estimatePoseSingleMarkers(markerCorners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);

        for (int i = 0; i < markerIds.size(); ++i)
        {
            cout << rvecs[i][0] << rvecs[i][1] << rvecs[i][2] << endl;
            cout << tvecs[i][0] << tvecs[i][1] << tvecs[i][2] << endl;
            cv::drawFrameAxes(img, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
        }

        imshow("img", img);
        if (waitKey(33) == 27)
            break;
    }

    destroyAllWindows();
    return 0;
}