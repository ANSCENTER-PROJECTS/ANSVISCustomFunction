# Custom Function Design Template for ANSVIS Server
This template offers a structured framework for designing custom analytic functions, models, or pipelines to seamlessly integrate and execute within the ANSVIS Server environment, utilizing OpenCV 4.7.

**Dependencies:**
- OpenCV 4.7: 
  - Installation: 
    - Release Version: [Download OpenCV 4.7.0](https://github.com/opencv/opencv/releases/download/4.7.0/opencv-4.7.0-windows.exe)
    - Build from Source: [OpenCV 4.7.0 Source](https://github.com/opencv/opencv/tree/4.7.0)

**Project settings:**
To compile and build the project successfully, users must ensure the correct configuration of Include Directories and Library Directories, directing them to the installed OpenCV directories.
**Steps:**
1. **Include Directories Configuration:**
   - Add the path to the OpenCV header files in your project's Include Directories settings. This enables the compiler to locate and include necessary header files during the build process.

2. **Library Directories Configuration:**
   - Specify the path to the OpenCV libraries in your project's Library Directories settings. This informs the linker about the location of OpenCV libraries required for linking during the build.
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/c8e59aca-6f52-4ac3-8685-0ff6711a9254)

3. **Add libraries to linker:**
Linker needs to include at least the opencv_core470.lib

![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/8cf779c8-357e-40e3-9324-da027a319c90)

# Design customised class
Use can design any custom analytic functions, models, or pipelines by implementing ANSCustomClass (inherited from IANSCustomClass).
All 5 virtual method needs to be overrided.
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/550c60e9-02d0-4280-985b-39142154f201)

**ANS Customised Function structure**
The ANS customised function structure folder contains 4 important parts as shown bellow:
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/8117a003-666e-4aff-8140-0a38ce3e2a2c)

- anscustom.txt (Required): This is the text file to inform ANSVIS to know that this is the supported custom model.
- ANSCustomCode.dll: This is the complied ANSCustomCode project that implement 5 overrided methods of ANSCustomClass.
- customised models: ANSVIS support onnx, OpenVINO, Pytorch, and Tensorflow.
- dependency library: Any code/models require dependency libaries, and these libraries have to be in the same folder.

**Prepare Customised Function Zip file**
After adding all required files to the folder as shown above, user has to zip this folder with the defaul zip password: AnsCustomModels20@$
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/a38b6d9a-34fd-479e-a1db-2666cca15cde)

![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/6c69cd72-4265-42ae-8170-7bd0b84239aa)

This modelzip file can be uploaded in the ANSVIS model page.

![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/0ae9ab8a-bfcf-43de-a8d1-502d5edb15d7)

![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/5b9b6636-4f94-41cb-a16f-42a44df66ce4)

**Implementing overrided methods**
User can use this template and re-implement overrided methods to achieve following tasks:
- Preprocessing: User can add any pre-processing methods to enhance input image
- Load and optimise AI models: User can load and optimise AI models (if required) by overriding LoadModel and OptimizedModel methods.
- Postproceswing: User can add any post-processing method to add more logic to inference result.
- AI pipeline inference: User can design any customised AI piple by joining mulitple AI models in customised logic and call the pipeline in RunInference method.
  This RunInference method can combile pre-processing, AI pipeline, customised business rules, and post processing.

The output of RunInference method is the arrray of CustomObject that contains important information for ANSVIS to process.
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/cd19ee83-20bc-444f-9c84-4b11bc1853e9)




