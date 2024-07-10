#include "pch.h"
#include "ANSCustomCode.h"
#include "YOLOv8Engine.h"
#include "trtinferencehandler.h"

// The zip password to zip the customised model: AnsCustomModels20@$
class CUSTOM_API ANSCustomClass : public IANSCustomClass
{
public:
    bool Initialize(const std::string& modelDirectory, std::string& labelMap) override;
    bool OptimizeModel(bool fp16) override;
    std::vector<CustomObject> RunInference(const cv::Mat& input) override;
    bool Destroy() override;
    ANSCustomClass();
    ~ANSCustomClass();

private:
    std::unique_ptr<YOLOv8Engine> m_engine; // Add YOLOv8Engine instance
};

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved)
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
}

bool ANSCustomClass::Initialize(const std::string& modelDirectory, std::string& labelMap)
{
    m_engine = std::make_unique<YOLOv8Engine>();
    return m_engine->Initialize(modelDirectory, labelMap);
}

bool ANSCustomClass::OptimizeModel(bool fp16)
{
    return m_engine ? m_engine->OptimizeModel(fp16) : false;
}

std::vector<CustomObject> ANSCustomClass::RunInference(const cv::Mat& input)
{
    return m_engine ? m_engine->RunInference(input) : std::vector<CustomObject>{};
}

bool ANSCustomClass::Destroy()
{
    m_engine.reset();
    return true;
}

ANSCustomClass::~ANSCustomClass()
{
    // Release resources
}

// expose the class to the outside world
extern "C" __declspec(dllexport) IANSCustomClass* Create()
{
    return new ANSCustomClass();
}
