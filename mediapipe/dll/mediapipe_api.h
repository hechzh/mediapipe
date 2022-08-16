#ifndef MEDIAPIPE_API_H_
#define MEDIAPIPE_API_H_

#include "mediapipe_interface.h"
#include <memory>

#ifndef DllExport
#define DllExport __declspec(dllexport)
#endif

DllExport MediapipeInterface* CreateMediapipeInterface();

#endif