#include "mediapipe/framework/port/integral_types.h"
#include "mediapipe/framework/type_map.h"
#include <string>
#include <vector>

#define MEDIAPIPE_REGISTER_GENERIC_TYPE(type)                                \
    MEDIAPIPE_REGISTER_TYPE(                                                 \
        mediapipe::type_map_internal::ReflectType<void(type*)>::Type, #type, \
        nullptr, nullptr)

#define MEDIAPIPE_REGISTER_GENERIC_TYPE_WITH_NAME(type, name)               \
    MEDIAPIPE_REGISTER_TYPE(                                                \
        mediapipe::type_map_internal::ReflectType<void(type*)>::Type, name, \
        nullptr, nullptr)

// Note: we cannot define a type which type hash id is already in the map.
// E.g. if tool::GetTypeHash<int>() == tool::GetTypeHash<int32>(), then only one
// can be registered.

MEDIAPIPE_REGISTER_GENERIC_TYPE(bool);
MEDIAPIPE_REGISTER_GENERIC_TYPE(double);
MEDIAPIPE_REGISTER_GENERIC_TYPE(float);
MEDIAPIPE_REGISTER_GENERIC_TYPE(int);
MEDIAPIPE_REGISTER_GENERIC_TYPE(int64);
MEDIAPIPE_REGISTER_GENERIC_TYPE(uint64);
MEDIAPIPE_REGISTER_GENERIC_TYPE(::std::vector<bool>);
MEDIAPIPE_REGISTER_GENERIC_TYPE(::std::vector<double>);
MEDIAPIPE_REGISTER_GENERIC_TYPE(::std::vector<float>);
MEDIAPIPE_REGISTER_GENERIC_TYPE(::std::vector<int>);
MEDIAPIPE_REGISTER_GENERIC_TYPE(::std::vector<int64>);
MEDIAPIPE_REGISTER_GENERIC_TYPE(::std::vector<std::string>);
MEDIAPIPE_REGISTER_GENERIC_TYPE(::std::vector<::std::vector<float>>);
MEDIAPIPE_REGISTER_GENERIC_TYPE_WITH_NAME(::std::string, "string");
