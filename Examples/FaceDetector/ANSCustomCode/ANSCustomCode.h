#ifndef ANSCUSTOMCODE_H
#define ANSCUSTOMCODE_H
#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "lite.h"
#define CUSTOM_API __declspec(dllexport)
struct CustomObject
{
    int classId{ 0 };
    int trackId{ 0 };
    std::string className{};
    float confidence{ 0.0 };
    cv::Rect box{};
    std::vector<cv::Point> polygon;
    cv::Mat mask;             //Json string mask ="point1.x,point1.y,...."
    std::vector<float> kps{};   // Pose exsimate keypoint
    std::string extraInfo;      // More information such as facial recognition
    std::string cameraId;
};
class CUSTOM_API IANSCustomClass
{
protected:
   std::string _modelDirectory; // The directory where the model is located
public:
    virtual bool Initialize(const std::string& modelDirectory, std::string& labelMap) = 0;
    virtual bool OptimizeModel(bool fp16) = 0;
    virtual std::vector<CustomObject> RunInference(const cv::Mat& input) = 0;
    virtual std::vector<CustomObject> RunInference(const cv::Mat& input, const std::string& camera_id) = 0;
    virtual bool Destroy() = 0;
};
// The zip password to zip the customised model: AnsCustomModels20@$
class CUSTOM_API ANSCustomClass : public IANSCustomClass
{
private:
    ortcv::SCRFD* face_detector;
public:
    bool Initialize(const std::string& modelDiretory, std::string& labelMap)override;
    bool OptimizeModel(bool fp16)override;
    std::vector<CustomObject> RunInference(const cv::Mat& input)override;
    std::vector<CustomObject> RunInference(const cv::Mat& input, const std::string& camera_id)override;
    bool Destroy()override;
    ANSCustomClass();
    ~ANSCustomClass();
};
#endif