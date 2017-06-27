1. Install Android Studio
2. Open tools->Android->SDK Manager
3. From SDK Platforms, select Android 4.0(IceCreamSandwich) and Android 7.1.1(Nougat)
4. From SDK Tools, select NDK, CMake, LLDB and install
5. Download Swig: http://www.swig.org

To auto-gen, from adaptivecards\src directory:
<swig directory>\swig.exe -c++ -java -package com.microsoft.adaptivecards.objectmodel -outdir main\java\com\microsoft\adaptivecards\objectmodel -o main\cpp\objectmodel_wrap.cpp AdaptiveCardObjectModel.i

To compile:
1. From Android Studio, New->"Import Project..."
2. Select folder "<github directory>\AdaptiveCards\source\android"
3. Build->"Rebuild Project"

To generate APK:
1. Follow "To compile" section
2. Build->"Build APK" or "Generate Signed APK..."

TODO:
1. Speech
2. AdaptiveCard
    a. actions
    b. version
    c. minVersion
    d. fallbackText
3. TextBlock
    a. Font Family
4. Image
    a. Not sure why "bitmap = BitmapFactory.decodeStream(inputStream);" sometimes returns null
    b. altText
5. Separation (ColumnSet, Column, ImageSet, FactSet, Input.Text)
    a. Horizontal line???
    b. Input.Text (only contains one separation config - normal vs strong?)
6. SelectAction (Column, Image)
8. Input.Number
9. Input.Date
10. Input.Time
11. Input.Toggle
12. Input.ChoiceSet

