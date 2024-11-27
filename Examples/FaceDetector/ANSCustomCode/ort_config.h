#pragma once

#ifndef LITE_AI_ORT_CORE_ORT_CONFIG_H
#define LITE_AI_ORT_CORE_ORT_CONFIG_H

#include "ort_defs.h"
#include "lite.ai.headers.h"
#include "onnxruntime_cxx_api.h"

inline static std::string OrtCompatiableGetInputName(size_t index, OrtAllocator* allocator,
    Ort::Session* ort_session) {
    return std::string(ort_session->GetInputNameAllocated(index, allocator).get());

}

inline static std::string OrtCompatiableGetOutputName(size_t index, OrtAllocator* allocator,
    Ort::Session* ort_session) {
    return std::string(ort_session->GetOutputNameAllocated(index, allocator).get());
}

namespace core {}

#endif //LITE_AI_ORT_CORE_ORT_CONFIG_H