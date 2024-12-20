#include "pch.h"
#include "ANSCustomCode.h"
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

ANSCustomClass::ANSCustomClass()
{
    // Initialize the model
}
bool ANSCustomClass::OptimizeModel(bool fp16)
{
    // Optimize the model
    // User can access to the _modelDirectory to get the models' path
    // User can start doing the optimization here for each model
    return true;
}

std::vector<CustomObject> ANSCustomClass::RunInference(const cv::Mat& input)
{
    // Run inference on the input image
    std::vector<CustomObject> results;
    std::vector<lite::types::BoxfWithLandmarks> detected_boxes;
    
    this->face_detector->detect(input, detected_boxes);
    for (const auto& box : detected_boxes)
    {
        CustomObject obj;
        obj.classId = 0; // Class Id now start from 0
        obj.trackId = 0;
        obj.className = "Face";
        obj.confidence = float(box.box.score);
        obj.box = box.box.rect();
        obj.mask = input;
        obj.extraInfo = "Custom";
		for (cv::Point2f point : box.landmarks.points)
		{
			obj.kps.push_back(point.x);
			obj.kps.push_back(point.y);
		}
		// kps will include x1, y1, x2, y2, x3, y3, x4, y4, x5, y5
        obj.polygon = { cv::Point(10, 10), cv::Point(20, 20), cv::Point(30, 30) };
		obj.cameraId = "FaceOrtCam";
        results.push_back(obj);
    }
    return results;
}

std::vector<CustomObject> ANSCustomClass::RunInference(const cv::Mat& input, const std::string& camera_id) {
    // Run inference on the input image
    std::vector<CustomObject> results;
    std::vector<lite::types::BoxfWithLandmarks> detected_boxes;
    this->face_detector->detect(input, detected_boxes);

    for (const auto& box : detected_boxes)
    {
        CustomObject obj;
		float detectionScore = float(box.box.score);
        if (detectionScore >= _detectionScoreThreshold) {
            obj.classId = 0; // Class ID now starts from 0
            obj.trackId = 0;
            obj.className = "Face";
            obj.confidence = float(box.box.score);
            obj.box = box.box.rect();
            obj.mask = input;
            obj.extraInfo = "Custom";
            for (cv::Point2f point : box.landmarks.points)
            {
                obj.kps.push_back(point.x);
                obj.kps.push_back(point.y);
            }
            // kps will include x1, y1, x2, y2, x3, y3, x4, y4, x5, y5
            obj.polygon = { cv::Point(10, 10), cv::Point(20, 20), cv::Point(30, 30) };
            obj.cameraId = camera_id;
            results.push_back(obj);
        }	
    }
    return results;
}

bool ANSCustomClass::Destroy()
{
    // Destroy any references
    return true;
}
bool ANSCustomClass::Initialize(const std::string& modelDirectory, float detectionScoreThreshold, std::string& labelMap)
{
    //1. The modelDirectory is supplied by ANSVIS and contains the path to the model files
    _modelDirectory = modelDirectory;
	_detectionScoreThreshold = detectionScoreThreshold;
    //2. User can start impelementing the initialization logic here
    std::string model_path = modelDirectory + "/scrfd.onnx";
    this->face_detector = new ortcv::SCRFD(model_path);

    //3 User also need to return the labelMap which is the name of the class
    labelMap = "Face";

    //4. Return true if the initialization is successful
    return true;
}
ANSCustomClass::~ANSCustomClass()
{
    // Release resources
    // Free memory
    // Close files
    // Close connections
    // etc.
	if (this->face_detector)
	{
		delete this->face_detector;
	}
}


// expose the class to the outside world
extern "C" __declspec(dllexport) IANSCustomClass* Create() {
    return new ANSCustomClass();
}