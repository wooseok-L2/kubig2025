#include </home/lws/kulws2025/kubig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/ml.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;
using namespace cv::ml;

String folderPath = "/home/lws/kulws2025/kubig2025/opencv/data/";

int main()
{
    vector<float> x_data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    vector<float> y_data;

    // 노이즈 추가.
    RNG rng(12345);
    for (auto &x : x_data)
    {
        float noise = rng.gaussian(0.5);
        y_data.push_back(2.f * x + 1.f + noise);
    }

    Mat samples(x_data.size(), 1, CV_32F);
    Mat response(y_data.size(), 1, CV_32F);
    for (size_t i = 0; i < x_data.size(); ++i)
    {
        samples.at<float>(i, 0) = x_data[i];
        response.at<float>(i, 0) = y_data[i];
    }

    Ptr<TrainData> tData = TrainData::create(samples, ROW_SAMPLE, response);

    // 값을 초기화.
    Mat X = Mat(samples.rows, 2, CV_32F);
    for (int i = 0; i < samples.rows; ++i)
    {
        X.at<float>(i, 0) = samples.at<float>(i, 0);
        X.at<float>(i, 1) = 1.0f;
    }

    // train
    Mat XtX = X.t() * X;
    Mat XtX_inv;
    invert(XtX, XtX_inv, DECOMP_SVD);
    Mat weights = XtX_inv * X.t() * response;

    cout << "기울기 weight :" << weights.at<float>(0, 0) << endl;
    cout << "절편 bias :" << weights.at<float>(1, 0) << endl;

    // predict
    float test_x = 15.0f;
    float predicted_y = weights.at<float>(0, 0) * test_x + weights.at<float>(1.0);
    cout << "결과 15.f : " << predicted_y << endl;

    return 0;
}