#ifndef HOLISTIC_TRACKING_H_
#define HOLISTIC_TRACKING_H_

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/opencv_core_inc.h"
#include "mediapipe/framework/port/status.h"
#include <functional>
#include <memory>
#include <string>

const std::string INPUT_STREAM = "input_video";
const std::string OUTPUT_STREAM = "output_video";
const std::string POSE_LANDMARKS = "pose_landmarks";
const std::string POSE_WORLD_LANDMARKS = "pose_world_landmarks";
const std::string LEFT_HAND_LANDMARKS = "left_hand_landmarks";
const std::string RIGHT_HAND_LANDMARKS = "right_hand_landmarks";
const std::string FACE_LANDMARKS = "face_landmarks";

class HolisticTracking {
public:
    HolisticTracking() = default;
    ~HolisticTracking() = default;

    bool Init(const std::string& graphPath, const std::string& basePath);
    void Detect(const cv::Mat& frame);
    void Release();

    void SetOnFrame(std::function<void(cv::Mat&)> callback);
    void SetOnPose(std::function<void(std::vector<std::vector<double>>&)> callback);
    void SetOnPoseWorld(std::function<void(std::vector<std::vector<double>>&)> callback);
    void SetOnLeftHand(std::function<void(std::vector<std::vector<double>>&)> callback);
    void SetOnRightHand(std::function<void(std::vector<std::vector<double>>&)> callback);
    void SetOnFace(std::function<void(std::vector<std::vector<double>>&)> callback);

private:
    bool MediaPipeInitGraph(const std::string& graphPath);
    bool MediaPipeRunGraph();
    void MediaPipeRelease();

    bool isInit_ = false;
    mediapipe::CalculatorGraph graph_;
    std::function<void(cv::Mat&)> frameCallback_;
    std::function<void(std::vector<std::vector<double>>&)> poseCallback_;
    std::function<void(std::vector<std::vector<double>>&)> poseWorldCallback_;
    std::function<void(std::vector<std::vector<double>>&)> leftHandCallback_;
    std::function<void(std::vector<std::vector<double>>&)> rightHandCallback_;
    std::function<void(std::vector<std::vector<double>>&)> faceCallback_;
};

#endif