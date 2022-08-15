#include "holistic_tracking.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/util/resource_util.h"

ABSL_DECLARE_FLAG(std::string, resource_root_dir);

bool HolisticTracking::Init(const std::string& graphPath, const std::string& basePath) {
    absl::SetFlag(&FLAGS_resource_root_dir, basePath);
    isInit_ = MediaPipeInitGraph(graphPath);
    return MediaPipeRunGraph();
}

void HolisticTracking::Detect(const cv::Mat& input) {
    auto inputFrame = absl::make_unique<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB, input.cols, input.rows, mediapipe::ImageFrame::kDefaultAlignmentBoundary);
    auto inputFrameMat = mediapipe::formats::MatView(inputFrame.get());
    input.copyTo(inputFrameMat);
    size_t frameTimestampUs = static_cast<double>(cv::getTickCount()) / static_cast<double>(cv::getTickFrequency()) * 1e6;
    graph_.AddPacketToInputStream(INPUT_STREAM, mediapipe::Adopt(inputFrame.release()).At(mediapipe::Timestamp(frameTimestampUs)));
}

void HolisticTracking ::Release() {
    MediaPipeRelease();
}

void HolisticTracking::SetOnFrame(std::function<void(cv::Mat&)> callback) {
    frameCallback_ = callback;
}

void HolisticTracking::SetOnPose(std::function<void(std::vector<std::vector<double>>&)> callback) {
    poseCallback_ = callback;
}

void HolisticTracking::SetOnPoseWorld(std::function<void(std::vector<std::vector<double>>&)> callback) {
    poseWorldCallback_ = callback;
}

void HolisticTracking::SetOnLeftHand(std::function<void(std::vector<std::vector<double>>&)> callback) {
    leftHandCallback_ = callback;
}

void HolisticTracking::SetOnRightHand(std::function<void(std::vector<std::vector<double>>&)> callback) {
    rightHandCallback_ = callback;
}

void HolisticTracking::SetOnFace(std::function<void(std::vector<std::vector<double>>&)> callback) {
    faceCallback_ = callback;
}

bool HolisticTracking::MediaPipeInitGraph(const std::string& graphPath) {
    std::string calculator_graph_config_contents;
    mediapipe::file::GetContents(graphPath.c_str(), &calculator_graph_config_contents);
    auto config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(calculator_graph_config_contents);
    return graph_.Initialize(config).ok();
}

bool HolisticTracking::MediaPipeRunGraph() {
    if (isInit_) {
        auto frameCallback = [this](const mediapipe::Packet& packet) {
            auto& outputFrame = packet.Get<mediapipe::ImageFrame>();
            auto& outputMat = mediapipe::formats::MatView(&outputFrame);
            if(frameCallback_!=nullptr){
                frameCallback_(outputMat);
            }
            return absl::OkStatus();
        };
        graph_.ObserveOutputStream(OUTPUT_STREAM, frameCallback);

        auto poseCallback = [this](const mediapipe::Packet& packet) {
            auto& poseLandmarkList = packet.Get<mediapipe::NormalizedLandmarkList>();
            std::vector<std::vector<double>> res;
            for (int i = 0; i < poseLandmarkList.landmark_size(); ++i) {
                const auto& landmark = poseLandmarkList.landmark(i);
                res.push_back({landmark.x(), landmark.y(), landmark.z(), landmark.visibility(), landmark.presence()});
            }
            if(poseCallback_!=nullptr){
                poseCallback_(res);
            }
            return absl::OkStatus();
        };
        graph_.ObserveOutputStream(POSE_LANDMARKS, poseCallback);

        auto poseWorldCallback = [this](const mediapipe::Packet& packet) {
            auto& poseWorldLandmarkList = packet.Get<mediapipe::LandmarkList>();
            std::vector<std::vector<double>> res;
            for (int i = 0; i < poseWorldLandmarkList.landmark_size(); ++i) {
                const auto& landmark = poseWorldLandmarkList.landmark(i);
                res.push_back({landmark.x(), landmark.y(), landmark.z(), landmark.visibility(), landmark.presence()});
            }
            if (poseWorldCallback_ != nullptr) {
                poseWorldCallback_(res);
            }
            return absl::OkStatus();
        };
        graph_.ObserveOutputStream(POSE_WORLD_LANDMARKS, poseWorldCallback);

        auto leftHandCallback = [this](const mediapipe::Packet& packet) {
            auto& leftHandLandmarkList = packet.Get<mediapipe::NormalizedLandmarkList>();
            std::vector<std::vector<double>> res;
            for (int i = 0; i < leftHandLandmarkList.landmark_size(); ++i) {
                const auto& landmark = leftHandLandmarkList.landmark(i);
                res.push_back({landmark.x(), landmark.y(), landmark.z(), landmark.visibility(), landmark.presence()});
            }
            if (leftHandCallback_ != nullptr) {
                leftHandCallback_(res);
            }
            return absl::OkStatus();
        };
        graph_.ObserveOutputStream(LEFT_HAND_LANDMARKS, leftHandCallback);

        auto rightHandCallback = [this](const mediapipe::Packet& packet) {
            auto& rightHandLandmarkList = packet.Get<mediapipe::NormalizedLandmarkList>();
            std::vector<std::vector<double>> res;
            for (int i = 0; i < rightHandLandmarkList.landmark_size(); ++i) {
                const auto& landmark = rightHandLandmarkList.landmark(i);
                res.push_back({landmark.x(), landmark.y(), landmark.z(), landmark.visibility(), landmark.presence()});
            }
            if (rightHandCallback_ != nullptr) {
                rightHandCallback_(res);
            }
            return absl::OkStatus();
        };
        graph_.ObserveOutputStream(RIGHT_HAND_LANDMARKS, rightHandCallback);

        auto faceCallback = [this](const mediapipe::Packet& packet) {
            auto& faceLandmarkList = packet.Get<mediapipe::NormalizedLandmarkList>();
            std::vector<std::vector<double>> res;
            for (int i = 0; i < faceLandmarkList.landmark_size(); ++i) {
                const auto& landmark = faceLandmarkList.landmark(i);
                res.push_back({landmark.x(), landmark.y(), landmark.z(), landmark.visibility(), landmark.presence()});
            }
            if (faceCallback_ != nullptr) {
                faceCallback_(res);
            }
            return absl::OkStatus();
        };
        graph_.ObserveOutputStream(FACE_LANDMARKS, faceCallback);

        return graph_.StartRun({}).ok();
    } else {
        LOG(INFO) << "Mediapipe graph not init.";
        return false;
    }
}

void HolisticTracking::MediaPipeRelease() {
    graph_.CloseInputStream(INPUT_STREAM);
    graph_.WaitUntilDone();
}