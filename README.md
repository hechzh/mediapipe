![MediaPipe](docs/logo.png) 

[MediaPipe](https://github.com/google/mediapipe)使用TFLite进行推理，在移动设备上有着优秀的性能。

尽管MediaPipe在PC中使用CPU也能达到较好的效果，但是在部分Solutions中的表现不尽如人意（比如[Holistic](https://google.github.io/mediapipe/solutions/holistic.html)）。

目前，MediaPipe只支持Linux的[GPU加速](https://google.github.io/mediapipe/getting_started/gpu_support.html)，Windows下无法使用GPU进行推理加速。

本项目使用[ONNX Runtime](https://github.com/microsoft/onnxruntime)，为MediaPipe增加了CUDA和TensorRT支持，使Windows也能进行GPU加速。

## 如何使用

1. 为了在Windows下使用GPU加速，首先需要安装英伟达相关依赖：

    - [CUDA](https://developer.nvidia.com/cuda-toolkit)
    - [cuDNN](https://developer.nvidia.com/cudnn)
    - [TensorRT(如果你想使用TensorRT进行推理)](https://developer.nvidia.com/tensorrt)

2. 安装[ONNX Runtime](https://github.com/microsoft/onnxruntime/releases)

3. 编译[Windows样例](/windows_build_example.md)

## 支持CUDA和TensorRT的Solutions

- [x] Face Detection
- [X] Hand Tracking
- [X] Pose Tracking
- [X] Holistic Tracking

## TODO

- [ ] face_landmark_with_attention模型无法使用

## BUG

1. 编译使用CPU的样例，也依赖onnxruntime.dll（如果有人知道如何解决，欢迎PR）。

## 其他

如果LOGO和开源许可侵犯了您的权益，请立即联系我，谢谢。