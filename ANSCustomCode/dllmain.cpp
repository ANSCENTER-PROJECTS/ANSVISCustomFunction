#include "pch.h"
#include "ANSCustomCode.h"

// The zip password to zip the customised model: AnsCustomModels20@$
class CUSTOM_API ANSCustomClass: public IANSCustomClass
{
public:
    bool Initialize(const std::string& modelDiretory, std::string& labelMap)override;
    bool OptimizeModel(bool fp16)override;
    std::vector<CustomObject> RunInference(const cv::Mat& input)override;
    std::vector<CustomObject> RunInference(const cv::Mat& input, const std::string& camera_id)override;
    bool Destroy()override;
    ANSCustomClass();
    ~ANSCustomClass();
};
BOOL APIENTRY DllMain( HMODULE hModule,
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

    //1. Preprocessing to enhance the image
    // User can implement the preprocessing logic here
        
    //2. Create AI model pipeline by combining the mutiple models in different ways
    // User can implement the AI model pipeline logic here
    // In this example, we will generate a random bounding box and return it as a result
    
     std::srand(std::time(0));
    // Generate random bounding box coordinates
    int x = std::rand() % input.cols;
    int y = std::rand() % input.rows;
    int width = std::rand() % (input.cols - x); // Ensure the box doesn't go outside the image
    int height = std::rand() % (input.rows - y); // Ensure the box doesn't go outside the image
    cv::Rect randomBox(x, y, width, height);
    CustomObject obj;
    obj.classId = 0;
    obj.trackId = 0;
    obj.className = "CName";
    obj.confidence = float(0.95);
    obj.box = randomBox;
    obj.mask = input;
    obj.extraInfo = "Extra Information";
    obj.kps = { 1.0, 2.0, 3.0, 4.0 };
    obj.polygon = { cv::Point(10, 10), cv::Point(20, 20), cv::Point(30, 30) };
	obj.cameraId = "Camera1";
    results.push_back(obj);

    //3. Cusomize business logic
    // User can implement the business logic here to modify the results

    //4. Postprocessing to enhance the results
    // User can implement the postprocessing logic here
	return results;
}
std::vector<CustomObject> ANSCustomClass::RunInference(const cv::Mat& input, const std::string& camera_id)
{
    // Run inference on the input image
    std::vector<CustomObject> results;

    //1. Preprocessing to enhance the image
    // User can implement the preprocessing logic here

    //2. Create AI model pipeline by combining the mutiple models in different ways
    // User can implement the AI model pipeline logic here
    // In this example, we will generate a random bounding box and return it as a result

    std::srand(std::time(0));
    // Generate random bounding box coordinates
    int x = std::rand() % input.cols;
    int y = std::rand() % input.rows;
    int width = std::rand() % (input.cols - x); // Ensure the box doesn't go outside the image
    int height = std::rand() % (input.rows - y); // Ensure the box doesn't go outside the image
    cv::Rect randomBox(x, y, width, height);
    CustomObject obj;
    obj.classId = 0;
    obj.trackId = 0;
    obj.className = "CName";
    obj.confidence = float(0.95);
    obj.box = randomBox;
    obj.mask = input;
    obj.extraInfo = "Extra Information";
    obj.kps = { 1.0, 2.0, 3.0, 4.0 };
    obj.polygon = { cv::Point(10, 10), cv::Point(20, 20), cv::Point(30, 30) };
	obj.cameraId = camera_id;
    results.push_back(obj);

    //3. Cusomize business logic
    // User can implement the business logic here to modify the results

    //4. Postprocessing to enhance the results
    // User can implement the postprocessing logic here
    return results;
}
bool ANSCustomClass::Destroy()
{
	// Destroy any references
	return true;
}
bool ANSCustomClass::Initialize(const std::string& modelDirectory,  std::string& labelMap)
{
    //1. The modelDirectory is supplied by ANSVIS and contains the path to the model files
    _modelDirectory = modelDirectory;

    //2. User can start impelementing the initialization logic here
    // Loading the model, initializing the model, etc.

    //3 User also need to return the labelMap which is the name of the class
    // In this example, we will return "CName" as the class name
    labelMap = "CName";

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
}


// expose the class to the outside world
extern "C" __declspec(dllexport) IANSCustomClass* Create() {
    return new ANSCustomClass();
}