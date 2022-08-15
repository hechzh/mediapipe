#ifndef HOLISTIC_TRACKING_H_
#define HOLISTIC_TRACKING_H_

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/opencv_core_inc.h"
#include "mediapipe/framework/port/status.h"
#include <memory>
#include <string>

class HolisticTracking {
public:
    HolisticTracking() = default;
    ~HolisticTracking() = default;

    bool Init(const std::string& graphPath, const std::string& basePath);
    void Detect(const cv::Mat& frame, cv::Mat& output);
    void Release();

private:
    bool MediaPipeInitGraph(const std::string& graphPath);
    bool MediaPipeRunGraph();
    void MediaPipeRelease();

    bool isInit_ = false;
    const char* inputStream = "input_video";
    const char* outputStream = "output_video";
    mediapipe::CalculatorGraph graph_;
    std::unique_ptr<mediapipe::OutputStreamPoller> poller_;
};

#endif