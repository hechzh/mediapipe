#ifndef HOLISTIC_TRACKING_API_H_
#define HOLISTIC_TRACKING_API_H_

#define DllExport __declspec(dllexport)

#include <opencv2/opencv.hpp>
#include <string>

DllExport bool Init(const std::string& graphPath, const std::string& basePath);

DllExport void Detect(const cv::Mat& input, cv::Mat& output);

#endif