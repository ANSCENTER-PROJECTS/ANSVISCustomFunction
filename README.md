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



