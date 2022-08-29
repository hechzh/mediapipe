#include "mediapipe_api.h"
#include "mediapipe_dll.h"

DllExport MediapipeInterface* CreateMediapipeInterface() {
    MediapipeInterface* interface = new MediapipeDll();
    return interface;
}
