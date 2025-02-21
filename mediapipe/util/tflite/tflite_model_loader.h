// Copyright 2020 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MEDIAPIPE_UTIL_TFLITE_TFLITE_MODEL_LOADER_H_
#define MEDIAPIPE_UTIL_TFLITE_TFLITE_MODEL_LOADER_H_

#include <functional>
#include <memory>
#include <string>

#include "mediapipe/framework/api2/packet.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/port/statusor.h"
#include "tensorflow/lite/core/shims/cc/model.h"

namespace mediapipe {
// Represents a TfLite model as a FlatBuffer.
using TfLiteModelPtr =
    std::unique_ptr<tflite_shims::FlatBufferModel,
                    std::function<void(tflite_shims::FlatBufferModel*)>>;

class TfLiteModelLoader {
public:
    // Returns a Packet containing a TfLiteModelPtr, pointing to a model loaded
    // from the specified file path.
    static absl::StatusOr<api2::Packet<TfLiteModelPtr>> LoadFromPath(
        const std::string& path);
};

}  // namespace mediapipe

#endif  // MEDIAPIPE_UTIL_TFLITE_TFLITE_MODEL_LOADER_H_
