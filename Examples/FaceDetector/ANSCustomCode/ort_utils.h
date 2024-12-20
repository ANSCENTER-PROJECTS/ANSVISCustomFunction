#pragma once

#ifndef LITE_AI_ORT_CORE_ORT_UTILS_H
#define LITE_AI_ORT_CORE_ORT_UTILS_H

#include "ort_config.h"

namespace ortcv
{
    // specific utils for ONNXRuntime
    namespace utils
    {
        namespace transform
        {
            enum
            {
                CHW = 0, HWC = 1
            };

            Ort::Value create_tensor(const cv::Mat& mat, const std::vector<int64_t>& tensor_dims,
                const Ort::MemoryInfo& memory_info_handler,
                std::vector<float>& tensor_value_handler,
                unsigned int data_format = CHW);

            cv::Mat normalize(const cv::Mat& mat, float mean, float scale);

            cv::Mat normalize(const cv::Mat& mat, const float mean[3], const float scale[3]);

            void normalize(const cv::Mat& inmat, cv::Mat& outmat, float mean, float scale);

            void normalize_inplace(cv::Mat& mat_inplace, float mean, float scale);

            void normalize_inplace(cv::Mat& mat_inplace, const float mean[3], const float scale[3]);
        }

    } // NAMESPACE UTILS
} // NAMESPACE ORTCV

#endif //LITE_AI_ORT_CORE_ORT_UTILS_H
