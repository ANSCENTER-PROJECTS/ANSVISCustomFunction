#ifndef LITE_AI_ORT_CORE_ORT_HANDLER_H
#define LITE_AI_ORT_CORE_ORT_HANDLER_H

#include "ort_config.h"

// global
namespace core
{
    // single input & multi outputs. not support for dynamic shape currently.
    class BasicOrtHandler
    {
    protected:
        Ort::Env ort_env;
        Ort::Session* ort_session = nullptr;
        const char* input_name = nullptr;
        std::vector<const char*> input_node_names;
        std::vector<std::string> input_node_names_;
        std::vector<int64_t> input_node_dims; // 1 input only.
        std::size_t input_tensor_size = 1;
        std::vector<float> input_values_handler;
        Ort::MemoryInfo memory_info_handler = Ort::MemoryInfo::CreateCpu(
            OrtArenaAllocator, OrtMemTypeDefault);
        std::vector<const char*> output_node_names;
        std::vector<std::string> output_node_names_;
        std::vector<std::vector<int64_t>> output_node_dims; // >=1 outputs
        const LITEORT_CHAR* onnx_path = nullptr;
        const char* log_id = nullptr;
        int num_outputs = 1;

    protected:
        const unsigned int num_threads; // initialize at runtime.

    protected:
        explicit BasicOrtHandler(const std::string& _onnx_path, unsigned int _num_threads = 1);

        virtual ~BasicOrtHandler();

        // un-copyable
    protected:
        BasicOrtHandler(const BasicOrtHandler&) = delete;

        BasicOrtHandler(BasicOrtHandler&&) = delete;

        BasicOrtHandler& operator=(const BasicOrtHandler&) = delete;

        BasicOrtHandler& operator=(BasicOrtHandler&&) = delete;

    protected:
        virtual Ort::Value transform(const cv::Mat& mat) = 0;

    private:
        void initialize_handler();
    };

}

#endif //LITE_AI_ORT_CORE_ORT_HANDLER_H