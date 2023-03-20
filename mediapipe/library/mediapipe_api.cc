#include "mediapipe_api.h"
#include "mediapipe_library.h"

LibraryExport FaceDetectInterface* CreateFaceDetectInterface() {
    FaceDetectInterface* interface = new FaceDetectLibrary();
    return interface;
}

LibraryExport FaceMeshInterface* CreateFaceMeshInterface() {
    FaceMeshInterface* interface  = new FaceMeshLibrary();
    return interface;
}