#ifndef MEDIAPIPE_DLL_H_
#define MEDIAPIPE_DLL_H_

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/opencv_core_inc.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe_interface.h"
#include "mediapipe_log.h"
#include "mediapipe_observer.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

const std::string INPUT_STREAM = "input_video";
const std::string OUTPUT_STREAM = "output_video";

class MediapipeDll : public MediapipeInterface {
public:
    MediapipeDll() = default;
    ~MediapipeDll() = default;
    using LandmarkCallback = std::function<void(std::vector<std::vector<double>>& landmarks)>;
    using MatCallback = std::function<void(cv::Mat& frame)>;

    void SetLogger(const std::shared_ptr<MediapipeLogger>& logger) override;
    void SetResourceDir(const std::string& path) override;
    void SetGraph(const std::string& path) override;
    void Detect(const cv::Mat& frame) override;
    void CreateObserver(const std::string& name, const LandmarkCallback& callback) override;
    void OpenPreview(const MatCallback& callback) override;
    void Start() override;
    void Stop() override;

private:
    std::shared_ptr<MediapipeLogger> logger_;
    std::map<std::string, std::shared_ptr<MediapipeObserver>> observer_;
    mediapipe::CalculatorGraph graph_;
};

#endif