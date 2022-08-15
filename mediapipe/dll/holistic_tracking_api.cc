#include "holistic_tracking_api.h"
#include "holistic_tracking.h"

HolisticTracking holisticTracking;

DllExport bool Init(const std::string& graphPath, const std::string& basePath) {
    return holisticTracking.Init(graphPath, basePath);
}

DllExport void Detect(const cv::Mat& input, cv::Mat& output) {
    holisticTracking.Detect(input, output);
}

DllExport void Release() {
    holisticTracking.Release();
}