# MediaPipe

## Face Detection

### short range

#### cpu

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/face_detection:face_detection_cpu_fps
bazel-bin/mediapipe/examples/desktop/face_detection/face_detection_cpu_fps.exe --calculator_graph_config_file=mediapipe/graphs/face_detection/face_detection_desktop_live.pbtxt --input_video_path=D:/video/cxk.mp4
```

#### onnx cuda

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/face_detection:face_detection_onnx_cuda_fps
bazel-bin/mediapipe/examples/desktop/face_detection/face_detection_onnx_cuda_fps.exe --calculator_graph_config_file=mediapipe/graphs/face_detection/face_detection_desktop_live_onnx_cuda.pbtxt --input_video_path=D:/video/cxk.mp4
```

#### onnx tensorrt

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/face_detection:face_detection_onnx_tensorrt_fps
bazel-bin/mediapipe/examples/desktop/face_detection/face_detection_onnx_tensorrt_fps.exe --calculator_graph_config_file=mediapipe/graphs/face_detection/face_detection_desktop_live_onnx_tensorrt.pbtxt --input_video_path=D:/video/cxk.mp4
```

### full range

#### cpu

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/face_detection:face_detection_full_range_cpu_fps
bazel-bin/mediapipe/examples/desktop/face_detection/face_detection_full_range_cpu_fps.exe --calculator_graph_config_file=mediapipe/graphs/face_detection/face_detection_full_range_desktop_live.pbtxt --input_video_path=D:/video/cxk.mp4
```

#### onnx cuda

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/face_detection:face_detection_full_range_onnx_cuda_fps
bazel-bin/mediapipe/examples/desktop/face_detection/face_detection_full_range_onnx_cuda_fps.exe --calculator_graph_config_file=mediapipe/graphs/face_detection/face_detection_full_range_desktop_live_onnx_cuda.pbtxt --input_video_path=D:/video/cxk.mp4
```

#### onnx tensorrt

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/face_detection:face_detection_full_range_onnx_tensorrt_fps
bazel-bin/mediapipe/examples/desktop/face_detection/face_detection_full_range_onnx_tensorrt_fps.exe --calculator_graph_config_file=mediapipe/graphs/face_detection/face_detection_full_range_desktop_live_onnx_tensorrt.pbtxt --input_video_path=D:/video/cxk.mp4
```

## Hand Tracking

### cpu

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/hand_tracking:hand_tracking_cpu_fps
bazel-bin/mediapipe/examples/desktop/hand_tracking/hand_tracking_cpu_fps.exe --calculator_graph_config_file=mediapipe/graphs/hand_tracking/hand_detection_desktop_live.pbtxt --input_video_path=D:/video/cxk.mp4
```

### cuda

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/hand_tracking:hand_tracking_onnx_cuda_fps
bazel-bin/mediapipe/examples/desktop/hand_tracking/hand_tracking_onnx_cuda_fps.exe --calculator_graph_config_file=mediapipe/graphs/hand_tracking/hand_detection_desktop_live_onnx_cuda.pbtxt --input_video_path=D:/video/cxk.mp4
```

### tensorrt

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/hand_tracking:hand_tracking_onnx_tensorrt_fps
bazel-bin/mediapipe/examples/desktop/hand_tracking/hand_tracking_onnx_tensorrt_fps.exe --calculator_graph_config_file=mediapipe/graphs/hand_tracking/hand_detection_desktop_live_onnx_tensorrt.pbtxt --input_video_path=D:/video/cxk.mp4
```

## Face Mesh

### cpu

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/face_mesh:face_mesh_cpu
bazel-bin/mediapipe/examples/desktop/face_mesh/face_mesh_cpu.exe --calculator_graph_config_file=mediapipe/graphs/face_mesh/face_mesh_desktop_live.pbtxt --input_video_path=D:/video/cxk.mp4
```

## Pose Tracking

### cpu

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/pose_tracking:pose_tracking_cpu_fps
bazel-bin/mediapipe/examples/desktop/pose_tracking/pose_tracking_cpu_fps.exe --calculator_graph_config_file=mediapipe/graphs/pose_tracking/pose_tracking_cpu.pbtxt --input_video_path=D:/video/cxk.mp4
```

### cuda

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/pose_tracking:pose_tracking_onnx_cuda_fps
bazel-bin/mediapipe/examples/desktop/pose_tracking/pose_tracking_onnx_cuda_fps.exe --calculator_graph_config_file=mediapipe/graphs/pose_tracking/pose_tracking_onnx_cuda.pbtxt --input_video_path=D:/video/cxk.mp4
```

### tensorrt

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/pose_tracking:pose_tracking_onnx_tensorrt_fps
bazel-bin/mediapipe/examples/desktop/pose_tracking/pose_tracking_onnx_tensorrt_fps.exe --calculator_graph_config_file=mediapipe/graphs/pose_tracking/pose_tracking_onnx_tensorrt.pbtxt --input_video_path=D:/video/cxk.mp4
```

## Holistic Tracking

### cpu

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/holistic_tracking:holistic_tracking_cpu_fps
bazel-bin/mediapipe/examples/desktop/holistic_tracking/holistic_tracking_cpu_fps.exe --calculator_graph_config_file=mediapipe/graphs/holistic_tracking/holistic_tracking_cpu.pbtxt --input_video_path=D:/video/cxk.mp4
```

### cuda

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/holistic_tracking:holistic_tracking_onnx_cuda_fps
bazel-bin/mediapipe/examples/desktop/holistic_tracking/holistic_tracking_onnx_cuda_fps.exe --calculator_graph_config_file=mediapipe/graphs/holistic_tracking/holistic_tracking_onnx_cuda.pbtxt --input_video_path=D:/video/cxk.mp4
```

### tensorrt

```bash
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/examples/desktop/holistic_tracking:holistic_tracking_onnx_tensorrt_fps
bazel-bin/mediapipe/examples/desktop/holistic_tracking/holistic_tracking_onnx_tensorrt_fps.exe --calculator_graph_config_file=mediapipe/graphs/holistic_tracking/holistic_tracking_onnx_tensorrt.pbtxt --input_video_path=D:/video/cxk.mp4
```