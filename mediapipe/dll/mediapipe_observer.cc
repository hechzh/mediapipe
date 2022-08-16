#include "mediapipe_observer.h"

MediapipeObserver::MediapipeObserver(const std::string& name,
                                     const std::shared_ptr<MediapipeLogger>& logger,
                                     const std::function<void(std::vector<std::vector<double>>& data)>& callback) : name_(name), logger_(logger), callback_(callback) {
}

const std::string& MediapipeObserver::GetName() const {
    return name_;
}

const MediapipeObserver::Callback& MediapipeObserver::GetCallback() const {
    return callback_;
}
