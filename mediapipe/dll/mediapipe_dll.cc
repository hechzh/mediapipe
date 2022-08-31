#include "mediapipe_dll.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/modules/face_geometry/protos/face_geometry.pb.h"
#include "mediapipe/util/resource_util.h"

ABSL_DECLARE_FLAG(std::string, resource_root_dir);

void MediapipeDll::SetLogger(const std::shared_ptr<MediapipeLogger>& logger) {
    logger_ = logger;
}

void MediapipeDll::SetResourceDir(const std::string& path) {
    absl::SetFlag(&FLAGS_resource_root_dir, path);
}

void MediapipeDll::SetGraph(const std::string& path) {
    std::string graphContent;
    mediapipe::file::GetContents(path, &graphContent);
    auto config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(graphContent);
    if (!graph_.Initialize(config).ok()) {
        logger_->Log("graph Initialize failed.");
    }
}

void MediapipeDll::Detect(const cv::Mat& input) {
    auto inputFrame = absl::make_unique<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB, input.cols, input.rows, mediapipe::ImageFrame::kDefaultAlignmentBoundary);
    auto inputFrameMat = mediapipe::formats::MatView(inputFrame.get());
    input.copyTo(inputFrameMat);
    size_t frameTimestampUs = static_cast<double>(cv::getTickCount()) / static_cast<double>(cv::getTickFrequency()) * 1e6;
    auto status = graph_.AddPacketToInputStream(INPUT_STREAM, mediapipe::Adopt(inputFrame.release()).At(mediapipe::Timestamp(frameTimestampUs)));
    if (!status.ok()) {
        logger_->Log("graph AddPacketToInputStream failed.");
    }
}

void MediapipeDll::GetFaceMesh(const LandmarkCallback& callback) {
    auto observer = std::make_shared<MediapipeObserver>("multi_face_geometry", logger_, nullptr);
    auto packetCallback = [&](const mediapipe::Packet& packet) {
        auto& landmarkList = packet.Get<std::vector<mediapipe::face_geometry::FaceGeometry>>();
        std::vector<std::vector<double>> res;
        for (const auto& landmark : landmarkList) {
            const auto& mesh = landmark.mesh();
            std::vector<double> temp;
            for (int r = 0; r < 468; ++r) {
                for (int c = 0; c < 5; ++c) {
                    temp.push_back(mesh.vertex_buffer(r * 5 + c));
                }
                res.push_back(temp);
            }
        }
        callback(res);
        return absl::OkStatus();
    };
    graph_.ObserveOutputStream("multi_face_geometry", packetCallback);
    observer_.emplace("multi_face_geometry", observer);
}

void MediapipeDll::CreateObserver(const std::string& name, const LandmarkCallback& callback) {
    auto observer = std::make_shared<MediapipeObserver>(name, logger_, callback);
    auto packetCallback = [&](const mediapipe::Packet& packet) {
        auto& landmarkList = packet.Get<mediapipe::NormalizedLandmarkList>();
        std::vector<std::vector<double>> res;
        for (int i = 0; i < landmarkList.landmark_size(); ++i) {
            const auto& landmark = landmarkList.landmark(i);
            res.push_back({landmark.x(), landmark.y(), landmark.z(), landmark.visibility(), landmark.presence()});
        }
        callback(res);
        return absl::OkStatus();
    };
    graph_.ObserveOutputStream(name, packetCallback);
    observer_.emplace(name, observer);
}

void MediapipeDll::OpenPreview(const MatCallback& callback) {
    auto matCallback = [&](const mediapipe::Packet& packet) {
        auto& outputFrame = packet.Get<mediapipe::ImageFrame>();
        auto& outputMat = mediapipe::formats::MatView(&outputFrame);
        callback(outputMat);
        return absl::OkStatus();
    };
    graph_.ObserveOutputStream(OUTPUT_STREAM, matCallback);
}

void MediapipeDll::Start() {
    if (!graph_.StartRun({}).ok()) {
        logger_->Log("graph StartRun failed.");
    }
}

void MediapipeDll::Stop() {
    graph_.CloseInputStream(INPUT_STREAM);
    graph_.WaitUntilDone();
    observer_.clear();
}