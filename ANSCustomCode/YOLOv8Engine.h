#ifndef YOLOV8ENGINE_H
#define YOLOV8ENGINE_H

#include "ANSCustomCode.h"
#include <memory>
#include "trtinferencehandler.h"

class YOLOv8Engine : public IANSCustomClass
{
private:
    std::unique_ptr<InferenceTRT> m_inference;
    std::string _modelDirectory;

public:
    bool Initialize(const std::string& modelDirectory, std::string& labelMap) override;
    bool OptimizeModel(bool fp16) override;
    std::vector<CustomObject> RunInference(const cv::Mat& input) override;
    bool Destroy() override;
};

#endif // YOLOV8ENGINE_H
