#include <iostream>
#include <opencv2/opencv.hpp>
#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    Mat img(400, 400, CV_8UC3, white);

    int a = 0, b = 0, c = 0;
    
    while(true)
    {
        img.setTo(white);
        
        line(img, Point(50, 50), Point(200 + a, 100 + a), blue, 3, LINE_AA);
        line(img, Point(70, 70), Point(220, 120), blue, 3, LINE_4);
        line(img, Point(90, 90), Point(240, 140), blue, 3, LINE_8);

        arrowedLine(img, Point(110, 110), Point(260, 160), orange, 3, LINE_8);
        arrowedLine(img, Point(130, 130), Point(280, 180), orange, 3, LINE_8, 0, 0.05);
        
        drawMarker(img, Point(50 + a, 200 + b), red, MARKER_CROSS);
        drawMarker(img, Point(50, 220), black, MARKER_DIAMOND);
        drawMarker(img, Point(50, 240), pink, MARKER_STAR);
        
        rectangle(img, Rect(250, 50, 50 + c, 50 + c), red, 2, LINE_AA);
        rectangle(img, Rect(300, 50, 50, 50), red, -1, LINE_AA);
        
        circle(img, Point(250, 250), 20, cyan, 2, LINE_AA);
        circle(img, Point(300, 300), 20, cyan, -1, LINE_AA);

        ellipse(img, Point(150, 300), Size(60, 30), 20, 0, 270, black, FILLED, LINE_AA);

        imshow("img", img);
    
        if (waitKey(33) == 27)
            break;

        a += 1;
        b -= 2;
        c += 3;
    }
    
    destroyAllWindows();

    return 0;
}