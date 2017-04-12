1. Install Android Studio
2. Open tools->Android->SDK Manager
3. From SDK Tools, select NDK, CMake, LLDB and install
4. Download Swig: http://www.swig.org

To auto-gen, from mobile directory:
<swig directory>\swig.exe -c++ -java -package com.microsoft.adaptivecards.objectmodel -outdir src\main\java\com\microsoft\adaptivecards\objectmodel -o src\main\cpp\objectmodel_wrap.cpp AdaptiveCardObjectModel.i

To compile:
1. From 
