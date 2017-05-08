1. Install Android Studio
2. Open tools->Android->SDK Manager
3. From SDK Tools, select NDK, CMake, LLDB and install
4. Download Swig: http://www.swig.org

To auto-gen, from mobile\src directory:
<swig directory>\swig.exe -c++ -java -package com.microsoft.adaptivecards.objectmodel -outdir main\java\com\microsoft\adaptivecards\objectmodel -o main\cpp\objectmodel_wrap.cpp AdaptiveCardObjectModel.i

To compile:
1. From Android Studio, New->"Import Project..."
2. Select folder "<github directory>\AdaptiveCards\source\android"
3. Build->"Rebuild Project"

To generate APK:
1. Follow "To compile" section
2. Build->"Build APK" or "Generate Signed APK..."

TODO:
ImageStyle
