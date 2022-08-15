#include "holistic_tracking.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/util/resource_util.h"

ABSL_DECLARE_FLAG(std::string, resource_root_dir);

bool HolisticTracking::Init(const std::string& graphPath, const std::string& basePath) {
    absl::SetFlag(&FLAGS_resource_root_dir, basePath);
    isInit_ = MediaPipeInitGraph(graphPath);
    return MediaPipeRunGraph();
}

void HolisticTracking::Detect(const cv::Mat& input, cv::Mat& output) {
    auto inputFrame = absl::make_unique<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB, input.cols, input.rows, mediapipe::ImageFrame::kDefaultAlignmentBoundary);
    auto inputFrameMat = mediapipe::formats::MatView(inputFrame.get());
    input.copyTo(inputFrameMat);
    size_t frameTimestampUs = static_cast<double>(cv::getTickCount()) / static_cast<double>(cv::getTickFrequency()) * 1e6;
    auto status = graph_.AddPacketToInputStream(inputStream, mediapipe::Adopt(inputFrame.release()).At(mediapipe::Timestamp(frameTimestampUs)));
    if (!status.ok()) {
        return;
    }
    mediapipe::Packet packet;
    if (!poller_->Next(&packet)) {
        return;
    }
    auto& outputFrame = packet.Get<mediapipe::ImageFrame>();
    auto& outputMat = mediapipe::formats::MatView(&outputFrame);
    outputMat.copyTo(output);
}

void HolisticTracking ::Release() {
    MediaPipeRelease();
    delete inputStream;
    delete outputStream;
}

bool HolisticTracking::MediaPipeInitGraph(const std::string& graphPath) {
    std::string calculator_graph_config_contents;
    mediapipe::file::GetContents(graphPath.c_str(), &calculator_graph_config_contents);
    auto config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(calculator_graph_config_contents);
    return graph_.Initialize(config).ok();
}

bool HolisticTracking::MediaPipeRunGraph() {
    if (isInit_) {
        auto status = graph_.AddOutputStreamPoller(outputStream);
        if (status.ok()) {
            poller_ = std::make_unique<mediapipe::OutputStreamPoller>(std::move(status.value()));
        } else {
            return false;
        }
        return graph_.StartRun({}).ok();
    } else {
        LOG(INFO) << "Mediapipe graph not init.";
        return false;
    }
}

void HolisticTracking::MediaPipeRelease() {
    graph_.CloseInputStream(inputStream);
    graph_.WaitUntilDone();
}