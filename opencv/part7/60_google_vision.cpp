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
    vector<String> files;
    files.push_back("beagle.jpg");
    files.push_back("cup.jpg");
    files.push_back("pineapple.jpg");
    files.push_back("scooter.jpg");
    files.push_back("space_shuttle.jpg");

    vector<Mat> imgs;
    for(auto &f : files)
        imgs.push_back(imread(folderPath+f));

    Net net = readNet(
        folderPath + "bvlc_googlenet.caffemodel",
        folderPath + "deploy.prototxt"
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

    int i = 0;
    for(auto &img : imgs)
    {
        Mat inputBlob = blobFromImage(img, 1, Size(224, 224), Scalar(104, 117, 123));
        net.setInput(inputBlob, "data");
        Mat prob = net.forward();

        double maxVal;
        Point maxLoc;
        minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);
        String str = format("%s (%4.2lf%%)", classNames[maxLoc.x].c_str(), maxVal * 100);
        putText(img, str, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255));
        imshow("img"+ to_string(i++), img);
    }

    waitKey();

    return 0;
}