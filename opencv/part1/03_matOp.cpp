#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    Mat img;
    Mat img2(100, 200, CV_8UC1);
    Mat img3(100, 200, CV_8UC3, Scalar(250, 210, 250)); // 빨간색  rgb X  bgr O
    Mat img4(Size(600, 800),CV_8UC3);
    img4.setTo(Scalar(0, 255, 0));

    Mat mat1 = Mat::zeros(3, 3, CV_32SC1);
    Mat mat2 = Mat::ones(3, 3, CV_32FC1);
    Mat mat3 = Mat::eye(3, 3, CV_32FC1);

    cout << "mat1 : " << mat1 << endl;
    cout << "mat2 : " << mat2 << endl;
    cout << "mat3 : " << mat3 << endl;

    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Mat mat4(2, 5, CV_32FC1, data);  
    
    cout << "mat4 : " << mat4 << endl;

    // imshow("img", img);
    imshow("img2", img2);
    imshow("img3", img3);
    waitKey();
    return 0;
}