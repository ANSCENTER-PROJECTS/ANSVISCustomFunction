
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include "..\\ANSCustomCode\ANSCustomCode.h"
int GPU11EngineImageTest(std::string modelFilePath, std::string imageFilePath) {

    ANSCustomClass faceDetector;
    std::string labelMap;
    std::string optmizedModelFolder;
    std::vector<std::string> classes;
    // Optimise model
    bool initialised = faceDetector.Initialize( modelFilePath.c_str(), labelMap);
	if (!initialised) {
		std::cout << "Failed to initialize model.\n";
		return -1;
	}

    // Optimise model
    std::cout << "Optimizing model, please wait...." << std::endl;
    std::cout << "Model is optmized, run inference...." << std::endl;
    bool optimisedResult = faceDetector.OptimizeModel(true);

    std::stringstream ss(labelMap);

    while (ss.good())
    {
        std::string substr;
        getline(ss, substr, ',');
        classes.push_back(substr);
    }
    cv::Mat frame = cv::imread(imageFilePath, cv::IMREAD_COLOR);
    unsigned int bufferLength = 0;
    auto start = std::chrono::system_clock::now();
    std::vector<CustomObject> results = faceDetector.RunInference(frame, "FaceOrtCam");
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("Time = %lld ms\n", static_cast<long long int>(elapsed.count()));

    for (auto result : results) {
		cv::rectangle(frame, result.box, 123, 2);
		cv::putText(frame, cv::format("%s:%d", classes[result.classId], result.classId), cv::Point(result.box.x, result.box.y - 5),
			0, 0.6, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);

		// Draw landmarks
		if (result.kps.size() > 0) {
			for (int i = 0; i < result.kps.size(); i += 2) {
				cv::circle(frame, cv::Point(result.kps[i], result.kps[i + 1]), 2, cv::Scalar(0, 255, 0), -1);
			}
		}
		std::cout << "Keypoints =[" << result.extraInfo << "]" << std::endl;
    }

 
    cv::imshow("ANS Custom face detector", frame);
    if (cv::waitKey(0) == 0) // Wait for 'esc' key press to exit
    {
        std::cout << "End of facial detection.\n";
    }
    cv::destroyAllWindows();

    std::cout << "End of program.\n";
    return 0;
}


int main()
{
	// Please change to correct path
	std::string modelFilePath = "C:\\Projects\\ANSVISCustomFunction\\Examples\\FaceDetector";
	std::string imageFilePath = "C:\\Projects\\ANSVISCustomFunction\\Examples\\FaceDetector\\test.jpg";
    GPU11EngineImageTest(modelFilePath, imageFilePath);
	return 0;
}

