#include "holistic_tracking_api.h"
#include "holistic_tracking.h"

HolisticTracking holisticTracking;

DllExport bool Init(const std::string& graphPath, const std::string& basePath) {
    return holisticTracking.Init(graphPath, basePath);
}

DllExport void Detect(const cv::Mat& input) {
    holisticTracking.Detect(input);
}

DllExport void Release() {
    holisticTracking.Release();
}

DllExport void SetFrameCallback(std::function<void(cv::Mat&)> callback) {
    holisticTracking.SetOnFrame(callback);
}

DllExport void SetPoseCallback(std::function<void(std::vector<std::vector<double>>&)> callback) {
    holisticTracking.SetOnPose(callback);
}

DllExport void SetPoseWorldCallback(std::function<void(std::vector<std::vector<double>>&)> callback) {
    holisticTracking.SetOnPoseWorld(callback);
}

DllExport void SetLeftHandCallback(std::function<void(std::vector<std::vector<double>>&)> callback) {
    holisticTracking.SetOnLeftHand(callback);
}

DllExport void SetRightHandCallback(std::function<void(std::vector<std::vector<double>>&)> callback) {
    holisticTracking.SetOnRightHand(callback);
}

DllExport void SetFaceCallback(std::function<void(std::vector<std::vector<double>>&)> callback) {
    holisticTracking.SetOnFace(callback);
}