# Custom Function Design Template for ANSVIS Server
This template offers a structured framework for designing custom analytic functions, models, or pipelines to seamlessly integrate and execute within the ANSVIS Server environment, utilizing OpenCV 4.7.

**Dependencies:**
- OpenCV 4.: 
  - Installation: 
    - Release Version: [Download OpenCV 4.10.0](https://storage.googleapis.com/anscenter-public-resources/runtime-engine/opencv.zip)
    - Build from Source: [OpenCV 4.10.0 Source](https://github.com/opencv/opencv)
  
  Download and place opencv in C:\opencv directory 
  ![image](https://github.com/user-attachments/assets/41e4e748-9185-4597-8955-de03d7795772)

- Visual Studio 2022: [Download Visual Studio VS2022](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false)
- Microsoft Visual C++ Redistributable
    - [VC++ x86](https://aka.ms/vs/17/release/vc_redist.x86.exe)
    - [VC++ x64](https://aka.ms/vs/17/release/vc_redist.x64.exe)

**Project settings:**
To compile and build the project successfully, users must ensure the correct configuration of Include Directories and Library Directories, directing them to the installed OpenCV directories.
**Steps:**
1. **Include Directories Configuration:**
   - Add the path to the OpenCV header files in your project's Include Directories settings. This enables the compiler to locate and include necessary header files during the build process.

2. **Library Directories Configuration:**
   - Specify the path to the OpenCV libraries in your project's Library Directories settings. This informs the linker about the location of OpenCV libraries required for linking during the build.
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/c8e59aca-6f52-4ac3-8685-0ff6711a9254)

3. **Add libraries to linker:**
Linker needs to include at least the opencv_world4100.lib

![image](https://github.com/user-attachments/assets/6307a523-1e89-488a-8328-311e7f8cb53b)


# Design customised class
Use can design any custom analytic functions, models, or pipelines by implementing ANSCustomClass (inherited from IANSCustomClass).
All 4 virtual method needs to be overrided.
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/fd2b07be-be04-406c-8bb8-e1b1d1aa7400)

**ANS Customised Function structure**
The ANS customised function structure folder contains 4 important parts as shown bellow:
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/f2858240-fb6e-4f6e-b60b-c8162eeab6c0)


- anscustom.txt (Required, the name can not be changed): This is the text file to inform ANSVIS to know that this is the supported custom model.
- ANSCustomCode.dll (Required, the name can not be changed): This is the complied ANSCustomCode project that implement 5 overrided methods of ANSCustomClass.
- Categories folder (Required, the name can not be changed): this folder contain files to that represents label names. For examples, labelmap contains 3 names: "name1,name2,name3".
  then the Categories will contain 3 files: name1.1, name2.2, name3.3
- classes.names (Required, the name can not be changed): is the text file contains labelmap names. 
- customised models (Optional, names can be varied): ANSVIS support onnx, OpenVINO, Pytorch, and Tensorflow.
- dependency library (Optional, names can be varied): Any code/models require dependency libaries, and these libraries have to be in the same folder.

***Categories folder***

![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/03ad7ae1-b458-4ed5-9b15-e2e1adeaa07d)

***classes.names file***

![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/17687818-e800-4416-b0ca-b5d66fc3a78e)



**Prepare Customised Function Zip file**
After adding all required files to the folder as shown above, user has to zip this folder with the defaul zip password: AnsCustomModels20@$
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/27d85372-738f-4fe5-b8ac-1d27ba00b7cc)

![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/6c69cd72-4265-42ae-8170-7bd0b84239aa)

This modelzip file can be uploaded in the ANSVIS model page.
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/8f5c16d7-6da3-4098-8615-81a76f41d204)

![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/43a4f5b1-7faa-4aec-bc1f-dc86bd5d7728)


**Implementing overrided methods**
User can use this template and re-implement overrided methods to achieve following tasks:
- Preprocessing: User can add any pre-processing methods to enhance input image
- Load and optimise AI models: User can load and optimise AI models (if required) by overriding Initialize and OptimizedModel methods.
- Postproceswing: User can add any post-processing method to add more logic to inference result.
- AI pipeline inference: User can design any customised AI piple by joining mulitple AI models in customised logic and call the pipeline in RunInference method.
  This RunInference method can combile pre-processing, AI pipeline, customised business rules, and post processing.

The output of RunInference method is the array of the CustomObject that contains important information for ANSVIS to process.
![image](https://github.com/ANSCENTER-PROJECTS/ANSVISCustomFunction/assets/7893168/cd19ee83-20bc-444f-9c84-4b11bc1853e9)

