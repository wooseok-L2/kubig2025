#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    Point_ <int> p1(1, 2);
    cout << p1 << endl;
    cout << "x : " << p1.x << "  " << "y : " << p1.y << endl;

    Point p2(3, 4);
    cout << p2 << endl;
    Point2f p3(3.12, 4.23);
    cout << p3 << endl;
    Point2d p4(1.1, 2.2);
    cout << p4 << endl;

    bool b1 = (p1 == p2);
    cout << b1 << endl;
    int d1 = p1.dot(p2);
    cout << d1 << endl;

    bool b2 = p2.inside(Rect(1, 1, 5, 5));
    cout << b2 << endl;

    Size sz1;
    Size2i sz2(10, 20);
    sz1.width = 10;
    sz1.height = 20;

    Size2f sz3 (3.14, 6.78);
    cout << "sz1.area() : " << sz1.area() << "    sz1.aspecRatio() : " << sz1.aspectRatio() << endl;

    Rect rc1;
    Rect rc2(10, 10, 20, 20);
    Rect rc3 = rc1 + Size(50, 40);
    Rect rc4 = rc2 + Point(10, 10);
    Rect rc5 = rc3 & rc4;
    Rect rc6 = rc3 | rc4;

    cout << "rc5 : " << rc5 << endl;
    cout << "rc6 : " << rc6 << endl;
    bool result = rc6.contains(p1);
    cout << result << endl;

    RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);
    Point2f pts[4];
    rr1.points(pts);

    Rect br = rr1.boundingRect();
    cout << "rr1 points : ";
    for (int i = 0; i < 4; i++)
    {
        cout << pts[i];
    }
    cout << "bounding Rect : " << br << endl;

    return 0;
}