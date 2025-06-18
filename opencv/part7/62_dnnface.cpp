#include "opencv2/opencv.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace cv;
using namespace cv::dnn;
using namespace std;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/part7/";

int main()
{

    VideoCapture cap(0);

    Net net = readNet(
        folderPath + "res10_300x300_ssd_iter_140000_fp16.caffemodel",
        folderPath + "ssd_deploy.prototxt"
    );

    ifstream fp(folderPath + "classification_classes_ILSVRC2012.txt");

    vector<String> classNames;
    String name;
    while(!fp.eof())
    {
        getline(fp, name);
        if (name.length())
            classNames.push_back(name);
    }

    Mat img;
    while(true)
    {
         cap >> img;
        Mat inputBlob = blobFromImage(img, 1, Size(300, 300), Scalar(104, 177, 123));
        net.setInput(inputBlob, "data");
        Mat res = net.forward(); // 실제 연산라인.

        Mat detect(res.size[2], res.size[3], CV_32FC1, res.ptr<float>());
        for (int i = 0; i < detect.rows; i++)
        {
            float confidence = detect.at<float>(i, 2);
            if (confidence < 0.5)
                break;

            int x1 = cvRound(detect.at<float>(i, 3) * img.cols);
            int y1 = cvRound(detect.at<float>(i, 4) * img.rows);
            int x2 = cvRound(detect.at<float>(i, 5) * img.cols);
            int y2 = cvRound(detect.at<float>(i, 6) * img.rows);

            rectangle(img, Rect(Point(x1, y1), Point(x2, y2)), Scalar(0, 255, 0));
            String str = format("Face: %4.3f", confidence);
            putText(img, str, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255), 2);
        }

        imshow("img", img);
        if (waitKey(3) == 27)
            break;
    }


    return 0;
}