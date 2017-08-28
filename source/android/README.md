1. Install Android Studio
2. Open tools->Android->SDK Manager
3. From SDK Platforms, select Android 4.0(IceCreamSandwich) and Android 7.1.1(Nougat)
4. From SDK Tools, select NDK, CMake, LLDB and install
5. Download Swig: http://www.swig.org

# To auto-gen, from adaptivecards\src directory:

## Windows
<swig directory>\swig.exe -c++ -java -package com.microsoft.adaptivecards.objectmodel -outdir main\java\com\microsoft\adaptivecards\objectmodel -o main\cpp\objectmodel_wrap.cpp AdaptiveCardObjectModel.i

## Mac
swig -c++ -java -package com.microsoft.adaptivecards.objectmodel -outdir main/java/com/microsoft/adaptivecards/objectmodel -o main/cpp/objectmodel_wrap.cpp AdaptiveCardObjectModel.i

# To compile:
1. From Android Studio, New->"Import Project..."
2. Select folder "<github directory>\AdaptiveCards\source\android"
3. Build->"Rebuild Project"

# To generate APK:
1. Follow "To compile" section
2. Build->"Build APK" or "Generate Signed APK..."

TODO:
1. Speech
2. AdaptiveCard
    a. version
    b. minVersion
    c. fallbackText
3. TextBlock
    a. Font Family
4. Image
    a. altText
5. Separation (ColumnSet, Column, ImageSet, FactSet, Input.Text)
    a. Horizontal line???
    b. Input.Text/Number,Date,Time,Toggle/ChoiceSet (only contains one separation config - normal vs strong?)
6. SelectAction (Column, Image)
7. HostConfig (Actions, Input.Text, Input.Number, Input.Date, Input.Time)

Questions:
Action - HTTP:
	- Should there be a callback to indicate success or failure and response data?
	- HTTP Header is missing in shared model

Input.Toggle - what is the difference in behavior between expanded vs compact? (ChoiceInputStyle)
Input.ChoiceSet - style is listed twice