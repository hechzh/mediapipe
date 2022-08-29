#ifndef MEDIAPIPE_OBSERVER_H_
#define MEDIAPIPE_OBSERVER_H_

#include "mediapipe_log.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

class MediapipeObserver {
public:
    MediapipeObserver(const std::string& name, const std::shared_ptr<MediapipeLogger>& logger, const std::function<void(std::vector<std::vector<double>>& data)>& callback);
    virtual ~MediapipeObserver() = default;

    using Callback = std::function<void(std::vector<std::vector<double>>& data)>;

    const std::string& GetName() const;
    double GetData(int index, int type) const;
    const Callback& GetCallback() const;

private:
    std::string name_;
    std::shared_ptr<MediapipeLogger> logger_;
    Callback callback_;
};

#endif