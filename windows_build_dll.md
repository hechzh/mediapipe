## mediapipe dll

bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/dll:mediapipe

## geometry_pipeline_metadata_landmarks

bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="D://Python//python.exe" mediapipe/modules/face_geometry/data:geometry_pipeline_metadata_landmarks