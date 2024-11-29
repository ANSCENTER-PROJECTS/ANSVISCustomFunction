# Custom Function Design Template for ANSVIS Server
This template offers a structured framework for designing custom analytic functions, models, or pipelines to seamlessly integrate and execute within the ANSVIS Server environment, utilizing OpenCV 4.10.

**Dependencies:**
- OpenCV 4.10: 
  - Installation: 
    - Release Version: [Download OpenCV 4.10.0](https://storage.googleapis.com/anscenter-public-resources/runtime-engine/opencv.zip)
    - Build from Source: [OpenCV 4.10.0 Source](https://github.com/opencv/opencv)

  - Please place it in C:\ directory (C:\opencv)
  ![image](https://github.com/user-attachments/assets/41e4e748-9185-4597-8955-de03d7795772)

- Visual Studio 2022: [Download Visual Studio VS2022](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false)
- Microsoft Visual C++ Redistributable
    - [VC++ x86](https://aka.ms/vs/17/release/vc_redist.x86.exe)
    - [VC++ x64](https://aka.ms/vs/17/release/vc_redist.x64.exe)

- Other Inference engines (optional)
    - Onnxruntime (1.20.1):
        - GPU version: https://github.com/microsoft/onnxruntime/releases/download/v1.20.1/onnxruntime-win-x64-gpu-1.20.1.zip
        - CPU version: https://github.com/microsoft/onnxruntime/releases/download/v1.20.1/onnxruntime-win-x86-1.20.1.zip
     Please download onnxruntime engine and place it in: C:\ directory (C:\onnxruntime-win-x64-gpu-1.20.1)
    
    - OpenVINO (2004.5.0):
      Download link: https://storage.openvinotoolkit.org/repositories/openvino/packages/2024.5/windows/w_openvino_toolkit_windows_2024.5.0.17288.7975fa5da0c_x86_64.zip
       Please download openvino engine and place it in: C:\ directory (C:\OpenVINO-2024.5.0)
    - TensorTR (10.6.0.26)
       Please download TensorRT engine and place it in: C:\ directory (C:\TensorRT-10.6.0.26)
    - NVIDIA CUDA 11.8 (https://developer.nvidia.com/cuda-11-8-0-download-archive?target_os=Windows&target_arch=x86_64&target_version=11)
    - NVIDIA CUDNN (8.9.7) for NVIDIA CUDA 11.8: please lace it in C:\ directory (C:\cudnn)

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
All 5 virtual method needs to be overrided.
![image](https://github.com/user-attachments/assets/2dadd524-287e-4b34-8c99-15e883dd85f9)

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

**Use Customised Model in ANSVIS**
In this repo, we have prepared a simple customised model to be used in ANSVIS. This model (ANSCustomModel_v4.zip), is located in Examples folder.

![image](https://github.com/user-attachments/assets/0c2d3f58-2b46-489b-817e-7211496526b9)

1. Launch ANSVIS
   ![image](https://github.com/user-attachments/assets/b1406a25-1599-497b-b796-1641a993b664)

2. Upload ANSCustomModel_v4.zip to ANSVIS
   In the model page, upload model to ANSVIS in 3 steps:
   
![image](https://github.com/user-attachments/assets/b0b17810-7e46-4b93-a592-e411d3d4759d)

![image](https://github.com/user-attachments/assets/fb4f781b-0207-4bae-a75d-cc12eee34b12)

3. Create AI Task using ANSCustomModel_v4 model
   + Create the AI Task by navigating to Task Group page, and add Server AI Task Group
     ![image](https://github.com/user-attachments/assets/ee0b8680-68a5-4e21-9c3c-7f69d1204c12)
  
  + Create AI Task Group: Select a camera
    ![image](https://github.com/user-attachments/assets/9b3ff339-287b-4c92-8601-507a40d53e40)

  + Create AI Task Group: Select customised model
    ![image](https://github.com/user-attachments/assets/c708245d-89bc-494b-af16-78b4a31d9bba)

  + Create AI Task Group: Create Rule
    ![image](https://github.com/user-attachments/assets/9275b1c8-e528-452a-a11d-69c8ac48567d)

    ![image](https://github.com/user-attachments/assets/cda23e3b-9af5-400d-9ff6-9e3f2d702ca2)

  + Create AI Task Group: Save Task
    ![image](https://github.com/user-attachments/assets/afa6ed0b-bcdd-48e2-846f-2db9ec687e36)

4. Run customised model and get the events

   ![image](https://github.com/user-attachments/assets/041e7347-e97b-4ddf-819d-c23f9bd45073)
   ![image](https://github.com/user-attachments/assets/ef64fa06-9308-4de9-b36d-2c44b8bd21fa)
   ![image](https://github.com/user-attachments/assets/880ff32a-9a0f-49e1-80bf-77693631b4c0)

   
 5. Add Face Detection example
  
  Please explore FaceDetector example that uses onnxruntime engine to for face detection task
    ![image](https://github.com/user-attachments/assets/8bdf144b-4d6e-402d-96e6-91ee4e8f52f4)

  
  Run FaceDetector-Unit test
    ![image](https://github.com/user-attachments/assets/624529db-7974-4eb8-9c7b-b1f3636b933d)



   ![image](https://github.com/user-attachments/assets/ca71ee73-f34d-44e4-9b49-79ccbb7ab263)
 

  
  Run face detection model on ANSVIS
  ![image](https://github.com/user-attachments/assets/fce47d55-fa96-4e60-b7f6-f63d40826138)

