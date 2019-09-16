1. Install Android Studio
2. Open tools->Android->SDK Manager
3. From SDK Platforms, select Android 4.0(IceCreamSandwich) and Android 7.1.1(Nougat)
4. From SDK Tools, select NDK, CMake, LLDB and install
5. Download Swig: http://www.swig.org (Mac `brew install swig`)

# Auto generate model

`cd source/android/adaptivecards/src`

## Windows

```console
<swig directory>\swig.exe -c++ -java -package io.adaptivecards.objectmodel -outdir main\java\io\adaptivecards\objectmodel -o main\cpp\objectmodel_wrap.cpp AdaptiveCardObjectModel.i
```

## Mac

```console
swig -c++ -java -package io.adaptivecards.objectmodel -outdir main/java/io/adaptivecards/objectmodel -o main/cpp/objectmodel_wrap.cpp AdaptiveCardObjectModel.i
```

# To compile:
1. From Android Studio, New->"Import Project..."
2. Select folder "<github directory>\AdaptiveCards\source\android"
3. Build->"Rebuild Project"

## Build failure "UnsupportedClassVersionError 52.0"

If you get a build failure similar to "UnsupportedClassVersionError 52.0" then from Android Studio go to: **File** -> **Other Settings** --> **Default project structure...** --> Check **Use Embedded JDK**


# To generate APK:
1. Follow "To compile" section
2. Build->"Build APK" or "Generate Signed APK..."

# To add adaptivecards library to new project:
1. add the following to the build.gradle of a project that will use the library
    compile 'io.adaptivecards:adaptivecards-android:1.2.0'
For more information, please go to http://search.maven.org/ and search adaptivecards-android

# To test
1. Follow steps 1 and 2 from [To compile](#to-compile) section
2. Select "mobile" or "mobilechatapp" project
3. Click "Run" button and select device (physical or virtual)
    3.1 If running the mobile app, you must copy the samples to the device
