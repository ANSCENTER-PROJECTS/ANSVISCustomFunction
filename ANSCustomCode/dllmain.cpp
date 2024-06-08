// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "ANSCustomCode.h"

class CUSTOM_API ANSCustomClass: public IANSCustomClass
{
public:
    bool Initialize(const std::string& modelZipFilePath, std::string& labelMap)override;
    bool LoadModel(const std::string& modelZipFilePath)override;
    bool OptimizeModel(bool fp16, std::string& optimizedModelFolder)override;
    std::vector<CustomObject> RunInference(const cv::Mat& input)override;
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
bool ANSCustomClass::OptimizeModel(bool fp16, std::string& optimizedModelFolder)
{
	// Optimize the model
	return true;
}
bool ANSCustomClass::LoadModel(const std::string& modelZipFilePath)
{
	// Load the model
    // The zip password: AnsCustomModels20@$
    	return true;
}
std::vector<CustomObject> ANSCustomClass::RunInference(const cv::Mat& input)
{
	// Run inference
	std::vector<CustomObject> results;

    // Dummy customised logic here
    CustomObject obj;
    obj.classId = 1;
    obj.trackId = 1;
    obj.className = "Custom Name";
    obj.confidence = float(0.95);
    obj.box = cv::Rect(10, 10, 100, 100);
    obj.mask = input;
    obj.extraInfo = "Extra Information";
    obj.kps = { 1.0, 2.0, 3.0, 4.0 };
    obj.polygon = { cv::Point(10, 10), cv::Point(20, 20), cv::Point(30, 30) };
    results.push_back(obj);

	return results;
}
bool ANSCustomClass::Destroy()
{
	// Destroy the model
	return true;
}
bool ANSCustomClass::Initialize(const std::string& modelZipFilePath,  std::string& labelMap)
{
    //The zip password: AnsCustomModels20@$
	// Initialize the model
	return true;
}
ANSCustomClass::~ANSCustomClass()
{
    // Release resources
}


// expose the class to the outside world
extern "C" __declspec(dllexport) IANSCustomClass* Create() {
    return new ANSCustomClass();
}