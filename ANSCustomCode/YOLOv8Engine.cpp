#include "pch.h"  // Bao gồm tiêu đề biên dịch trước
#include "YOLOv8Engine.h"
#include "trtinferencehandler.h"

bool YOLOv8Engine::Initialize(const std::string& modelDirectory, std::string& labelMap)
{
    // Khởi tạo mô hình
    try
    {
        m_inference = std::make_unique<InferenceTRT>(
            modelDirectory + "/yolov8s.onnx",  // Replace path 
            0.5f, 0.65f, 100, 32, 160, 160, 0.5f);
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error initialize YOLOv8Engine: " << ex.what() << std::endl;
        return false;
    }
    labelMap = "CName"; // Tên lớp ví dụ
    return true;
}

bool YOLOv8Engine::OptimizeModel(bool fp16)
{
    // Code here, if you want optimize model
    return true;
}

std::vector<CustomObject> YOLOv8Engine::RunInference(const cv::Mat& input)
{
    std::vector<CustomObject> results;
    try
    {
        auto objects = m_inference->detectObjects(input);
        for (const auto& obj : objects)
        {
            CustomObject customObj;
            customObj.classId = obj.label;
            customObj.trackId = 0;
            customObj.className = "CName";
            customObj.confidence = obj.probability;
            customObj.box = obj.rect;
            customObj.mask = obj.boxMask;
            customObj.kps = {}; // Key point
            customObj.extraInfo = "Infomation extra";
            results.push_back(customObj);
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error run inference: " << ex.what() << std::endl;
    }
    return results;
}

bool YOLOv8Engine::Destroy()
{
    return true;
}
