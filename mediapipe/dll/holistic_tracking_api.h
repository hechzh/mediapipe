#ifndef HOLISTIC_TRACKING_API_H_
#define HOLISTIC_TRACKING_API_H_

#ifndef DllExport
#define DllExport __declspec(dllexport)
#endif

#include <opencv2/opencv.hpp>
#include <functional>
#include <string>

DllExport bool Init(const std::string& graphPath, const std::string& basePath);

DllExport void Detect(const cv::Mat& input);

DllExport void Release();

DllExport void SetFrameCallback(std::function<void(cv::Mat&)>);

DllExport void SetPoseCallback(std::function<void(std::vector<std::vector<double>>&)> callback);

DllExport void SetPoseWorldCallback(std::function<void(std::vector<std::vector<double>>&)> callback);

DllExport void SetLeftHandCallback(std::function<void(std::vector<std::vector<double>>&)> callback);

DllExport void SetRightHandCallback(std::function<void(std::vector<std::vector<double>>&)> callback);

DllExport void SetFaceCallback(std::function<void(std::vector<std::vector<double>>&)> callback);

#endif