#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/opencv.hpp>
// #include </home/lws/kulws2025/kubig2025/opencv/part2/array.h>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
     // data
    String name = "Lws";
    int age = 10;
    Point pt1(100, 200);
    vector<int> scores = {80, 90, 50};
    Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);
    // Array array(10);

    String filename = folderPath + "mydata.yml";
    FileStorage fs;
    fs.open(filename, FileStorage::READ);
    fs["name"] >> name;
    fs["age"] >> age;
    fs["point"] >> pt1;
    fs["scores"] >> scores;
    fs["data"] >> mat1;
    // fs << "array" << array; // 빌드 통과 못함!

    fs.release();

    cout << "name : " << name << endl;
    cout << "age : " << age << endl;
    cout << "point : " << pt1 << endl;
    cout << "scores : " << Mat(scores).t() << endl;
    cout << "data : " << mat1 << endl;

    return 0;
}
