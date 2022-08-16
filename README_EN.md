![MediaPipe](docs/logo.png) 

[简体中文](README.md)

[MediaPipe](https://github.com/google/mediapipe) uses TFLite for inference and has excellent performance on mobile devices.

Although MediaPipe can achieve satisfactory performance using CPU in PC, it is not satisfactory in some Solutions (such as [Holistic](https://google.github.io/mediapipe/solutions/holistic.html)).

Currently, MediaPipe only supports [GPU acceleration](https://google.github.io/mediapipe/getting_started/gpu_support.html) for Linux，the GPU cannot be used for inference acceleration under Windows.

This project uses [ONNX Runtime](https://github.com/microsoft/onnxruntime), adds CUDA and TensorRT support to MediaPipe, and enables GPU acceleration on Windows

## How to use

1. In order to use GPU acceleration under Windows, you first need to install NVIDIA dependencies:

    - [CUDA](https://developer.nvidia.com/cuda-toolkit)
    - [cuDNN](https://developer.nvidia.com/cudnn)
    - [TensorRT(If you want to use TensorRT for inference)](https://developer.nvidia.com/tensorrt)

2. Install [ONNX Runtime](https://github.com/microsoft/onnxruntime/releases)

3. Build [Windows examples](/windows_build_example.md)

## Solutions that support CUDA and TensorRT

- [x] Face Detection
- [X] Hand Tracking
- [X] Pose Tracking
- [X] Holistic Tracking

## TODO

- [ ] face_landmark_with_attention model cannot be used.

## BUG

1. Build the sample using the CPU also depends on onnxruntime.dll (if anyone knows how to solve it, PR is welcome).

## Other

If the LOGO and open source license violate your rights, please contact me immediately, thank you.