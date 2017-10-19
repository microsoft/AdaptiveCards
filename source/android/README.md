1. Install Android Studio
2. Open tools->Android->SDK Manager
3. From SDK Platforms, select Android 4.0(IceCreamSandwich) and Android 7.1.1(Nougat)
4. From SDK Tools, select NDK, CMake, LLDB and install
5. Download Swig: http://www.swig.org (Mac `brew install swig`)

# Auto generate model

`cd source/android/adaptivecards/src`

## Windows

```console
<swig directory>\swig.exe -c++ -java -package com.microsoft.adaptivecards.objectmodel -outdir main\java\com\microsoft\adaptivecards\objectmodel -o main\cpp\objectmodel_wrap.cpp AdaptiveCardObjectModel.i
```

## Mac

```console
swig -c++ -java -package com.microsoft.adaptivecards.objectmodel -outdir main/java/com/microsoft/adaptivecards/objectmodel -o main/cpp/objectmodel_wrap.cpp AdaptiveCardObjectModel.i
```

# To compile:
1. From Android Studio, New->"Import Project..."
2. Select folder "<github directory>\AdaptiveCards\source\android"
3. Build->"Rebuild Project"

# To generate APK:
1. Follow "To compile" section
2. Build->"Build APK" or "Generate Signed APK..."

# To add adaptivecards library to new project:
1. add the following to the build.gradle of a project that will use the library
    compile 'io.adaptivecards:adaptivecards-android-arm:1.0.0'
For more information, please go to http://search.maven.org/ and search adaptivecards-android-arm
TODO:
1. Scenario->Restaurant.json is not rendered correctly
2. AdaptiveCard
    a. version
    b. minVersion
    c. fallbackText
3. TextBlock
    a. Font Family
4. Image
    a. altText
5. Separation - Container/ColumnSet
6. SelectAction (Column, Image)

Questions:
Action - HTTP:
	- Should there be a callback to indicate success or failure and response data?
	- HTTP Header is missing in shared model

