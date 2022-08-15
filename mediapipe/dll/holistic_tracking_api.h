#ifndef HOLISTIC_TRACKING_API_H_
#define HOLISTIC_TRACKING_API_H_

#ifndef DllExport
#define DllExport __declspec(dllexport)
#endif

#include <opencv2/opencv.hpp>
#include <string>

DllExport bool Init(const std::string& graphPath, const std::string& basePath);

DllExport void Detect(const cv::Mat& input, cv::Mat& output);

DllExport void Release();

#endif