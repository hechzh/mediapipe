#include "holistic_tracking_api.h"
#include <iostream>
#include <string>

constexpr char windowName[] = "MediaPipe";

int main() {
    cv::namedWindow(windowName);
    cv::VideoCapture capture;
    capture.open("D:/video/cxk.mp4");
    if (!capture.isOpened()) {
        std::cout << "VideoCapture is not open" << std::endl;
    }
    if (!Init("holistic_tracking_onnx_cuda.pbtxt", "D:/code/mediapipe/")) {
        std::cout << "Graph init fail." << std::endl;
        return -1;
    }
    bool grabFrames = true;
    while (grabFrames) {
        cv::Mat cameraFrameRaw;
        capture >> cameraFrameRaw;
        if (cameraFrameRaw.empty()) {
            // std::cout << "Empty frame." << std::endl;
            continue;
        }
        cv::Mat cameraFrame;
        cv::cvtColor(cameraFrameRaw, cameraFrame, cv::COLOR_BGR2RGB);
        Detect(cameraFrame, cameraFrameRaw);
        cv::cvtColor(cameraFrame, cameraFrameRaw, cv::COLOR_RGB2BGR);
        cv::imshow(windowName, cameraFrameRaw);
        const int pressed_key = cv::waitKey(5);
        if (pressed_key >= 0 && pressed_key != 255) grabFrames = false;
    }
    std::cout << "end" << std::endl;
    return 0;
}