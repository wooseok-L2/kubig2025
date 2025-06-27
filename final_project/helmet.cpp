#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <fstream>
#include <iostream>

using namespace cv;
using namespace dnn;
using namespace std;

// 클래스 이름을 읽어오는 함수
vector<string> readClassNames(const string& filename) {
    vector<string> classNames;
    ifstream ifs(filename.c_str());
    string line;
    while (getline(ifs, line)) classNames.push_back(line);
    return classNames;
}

int main() {
    string modelPath = "/home/lws/kulws2025/kubig2025/final_project/yolov5/helmet-yolo/yolov5s_helmet3/weights/best.onnx";
    string classNamesFile = "/home/lws/kulws2025/kubig2025/final_project/yolov5/helmet-yolo/yolov5s_helmet3/weights/classes.txt"; // "helmet", "person" 순서로 가정

    vector<string> classNames = readClassNames(classNamesFile);

    Net net = readNetFromONNX(modelPath);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CUDA); // CUDA 안 쓸 경우 DNN_TARGET_CPU

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "웹캠을 열 수 없습니다." << endl;
        return -1;
    }

    namedWindow("YOLOv5 Detection", WINDOW_NORMAL);
    resizeWindow("YOLOv5 Detection", 1280, 720);

    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        Mat blob;
        blobFromImage(frame, blob, 1/255.0, Size(640, 640), Scalar(), true, false);
        net.setInput(blob);

        vector<Mat> outputs;
        net.forward(outputs, net.getUnconnectedOutLayersNames());

        float* data = (float*)outputs[0].data;
        const int dimensions = outputs[0].size[2];
        const int rows = outputs[0].size[1];

        vector<Rect> persons, helmets;

        for (int i = 0; i < rows; ++i) {
            float confidence = data[i * dimensions + 4];
            if (confidence < 0.5) continue;

            float* classScores = data + i * dimensions + 5;
            Mat scores(1, classNames.size(), CV_32FC1, classScores);
            Point classIdPoint;
            double maxClassScore;
            minMaxLoc(scores, 0, &maxClassScore, 0, &classIdPoint);

            float finalConfidence = confidence * (float)maxClassScore;
            if (finalConfidence < 0.5) continue;

            if (maxClassScore > 0.5) {
                int centerX = (int)(data[i * dimensions] * frame.cols);
                int centerY = (int)(data[i * dimensions + 1] * frame.rows);
                int width = (int)(data[i * dimensions + 2] * frame.cols);
                int height = (int)(data[i * dimensions + 3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;
                Rect box(left, top, width, height);

                string label = classNames[classIdPoint.x];
                if (label == "person") {
                    persons.push_back(box);
                } else if (label == "helmet") {
                    helmets.push_back(box);
                }
            }
        }

        for (const Rect& person : persons) {
            bool hasHelmet = false;
            for (const Rect& helmet : helmets) {
                if ((person & helmet).area() > 0) {
                    hasHelmet = true;
                    rectangle(frame, helmet, Scalar(255, 0, 0), 2); // 파란색 helmet
                }
            }
            if (hasHelmet) {
                rectangle(frame, person, Scalar(0, 255, 0), 2); // 초록색 person
            } else {
                rectangle(frame, person, Scalar(0, 0, 255), 2); // 빨간색 person (헬멧 없음)
            }
        }

        imshow("YOLOv5 Detection", frame);
        if (waitKey(1) == 27) break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
