// 카메라 켜서 frame 확보
// 색 공간 -> hsv 로 변경 clone() 해서 따로 처리.
// 양방향 필터 처리
// inrange -> 색종이를 인식
// morph 함수 -> 이진화 Mat 정리
// labeling
// 화면에 rectangle 로 표시
// putText, ft2 로 색종이 or color-paper
// 사각형과 폰트는 색종이를 따라다녀야 함!
#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

Ptr<cv::freetype::FreeType2> rapperFreeTypeCenterSetup(const String &fontpath)
{
    Ptr<cv::freetype::FreeType2> ft2 = freetype::createFreeType2();
    ft2->loadFontData(fontpath, 0);
    return ft2;
}

void rapperFreeTypeCenter(Mat &img, Ptr<cv::freetype::FreeType2> ft2, const String &text, const int &textHeight, const int &thickness, const int &line_type, const Scalar &color, const Point &textOrg, const bool &withRect)
{
    Size textSize = ft2->getTextSize(text, textHeight, -1, 0) + Size(0, 20);
    // bottom padding을 위해 높이 20 추가
    Point top_left((textOrg.x - textSize.width), (textOrg.y - textSize.height));
    Rect textRect(top_left, textSize);
    if (withRect)
    {
        rectangle(img, textRect, color, 3, line_type); // 텍스트 영역 사각형 그리기
    }

    ft2->putText(img, text, textRect.tl(), textHeight, color, thickness, line_type, false);
}

int main()
{
    // 카메라 켜서 frame 확보
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Error: Could not open camera." << endl;
        return -1;
    }

    // FreeType2 초기화
    auto ft2 = rapperFreeTypeCenterSetup("/home/lws/kulws2025/kubig2025/opencv/data/NanumPenScript-Regular.ttf");

    Mat frame, hsv, hsv_clone, blurred, mask, morph;
    int low, high;
    namedWindow("Color Paper Detection");
    createTrackbar("hue-lower", "Color Paper Detection", &low, 255);
    createTrackbar("hue-high", "Color Paper Detection", &high, 255);

    while (true)
    {
        // 프레임 캡처
        cap >> frame;
        if (frame.empty())
        {
            cout << "Error: Could not read frame." << endl;
            break;
        }

        // 색 공간 -> HSV로 변경 및 clone()
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        hsv_clone = hsv.clone();

        // 양방향 필터 처리
        bilateralFilter(hsv_clone, blurred, 9, 75, 75);

        // inRange -> 색종이 인식 (예: 빨간색 종이, HSV 범위 설정)
        Scalar lower_red(0, 0, 0);
        Scalar upper_red(164, 255, 255);
        inRange(blurred, lower_red, upper_red, mask);
        bitwise_not(mask, mask);

        // morph 함수 -> 이진화 Mat 정리
        Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
        morphologyEx(mask, morph, MORPH_OPEN, kernel);
        morphologyEx(morph, morph, MORPH_CLOSE, kernel);
        imshow("morph", morph);

        // Labeling
        Mat labels, stats, centroids;
        int num_labels = connectedComponentsWithStats(morph, labels, stats, centroids);

        // 화면에 rectangle 및 텍스트 표시
        for (int i = 1; i < num_labels; i++)
        {
            // stats 에서 픽셀의 수가 500 이상이면 조건
            if (stats.at<int>(i, CC_STAT_AREA) < 500)
                continue;
            int x = stats.at<int>(i, CC_STAT_LEFT);
            int y = stats.at<int>(i, CC_STAT_TOP);
            int width = stats.at<int>(i, CC_STAT_WIDTH);
            int height = stats.at<int>(i, CC_STAT_HEIGHT);

            // Rectangle 그리기
            rectangle(frame, Point(x, y), Point(x + width, y + height), Scalar(0, 255, 0), 2);

            // putText with FreeType2로 "color-paper" 표시
            rapperFreeTypeCenter(frame, ft2, "color-paper", 50, 2, LINE_AA, black, Point(x, y), true);
        }

        // 결과 화면 표시
        imshow("Color Paper Detection", frame);

        // 'q' 키로 종료
        if (waitKey(1) == 27)
        {
            break;
        }
    }

    // 자원 해제
    cap.release();
    destroyAllWindows();
    return 0;
}