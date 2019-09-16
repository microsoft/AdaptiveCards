# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

include_directories(../../shared/cpp/ObjectModel
                    ../../shared/cpp/ObjectModel/json)

add_library( # Sets the name of the library.
             adaptivecards-native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ../../shared/cpp/ObjectModel/jsoncpp.cpp
             ../../shared/cpp/ObjectModel/ActionParserRegistration.cpp
             ../../shared/cpp/ObjectModel/AdaptiveBase64Util.cpp
             ../../shared/cpp/ObjectModel/ActionSet.cpp
             ../../shared/cpp/ObjectModel/AdaptiveCardParseException.cpp
             ../../shared/cpp/ObjectModel/AdaptiveCardParseWarning.cpp
             ../../shared/cpp/ObjectModel/BaseActionElement.cpp
             ../../shared/cpp/ObjectModel/BackgroundImage.cpp
             ../../shared/cpp/ObjectModel/BaseCardElement.cpp
             ../../shared/cpp/ObjectModel/BaseElement.cpp
             ../../shared/cpp/ObjectModel/BaseInputElement.cpp
             ../../shared/cpp/ObjectModel/ChoiceInput.cpp
             ../../shared/cpp/ObjectModel/ChoiceSetInput.cpp
             ../../shared/cpp/ObjectModel/Column.cpp
             ../../shared/cpp/ObjectModel/ColumnSet.cpp
             ../../shared/cpp/ObjectModel/CollectionTypeElement.cpp
             ../../shared/cpp/ObjectModel/Container.cpp
             ../../shared/cpp/ObjectModel/DateInput.cpp
             ../../shared/cpp/ObjectModel/DateTimePreparsedToken.cpp
             ../../shared/cpp/ObjectModel/DateTimePreparser.cpp
             ../../shared/cpp/ObjectModel/ElementParserRegistration.cpp
             ../../shared/cpp/ObjectModel/Enums.cpp
             ../../shared/cpp/ObjectModel/Fact.cpp
             ../../shared/cpp/ObjectModel/FactSet.cpp
             ../../shared/cpp/ObjectModel/FeatureRegistration.cpp
             ../../shared/cpp/ObjectModel/HostConfig.cpp
             ../../shared/cpp/ObjectModel/Image.cpp
             ../../shared/cpp/ObjectModel/ImageSet.cpp
             ../../shared/cpp/ObjectModel/Inline.cpp
             ../../shared/cpp/ObjectModel/MarkDownBlockParser.cpp
             ../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.cpp
             ../../shared/cpp/ObjectModel/MarkDownParsedResult.cpp
             ../../shared/cpp/ObjectModel/MarkDownParser.cpp
             ../../shared/cpp/ObjectModel/Media.cpp
             ../../shared/cpp/ObjectModel/MediaSource.cpp
             ../../shared/cpp/ObjectModel/NumberInput.cpp
             ../../shared/cpp/ObjectModel/OpenUrlAction.cpp
             ../../shared/cpp/ObjectModel/ParseContext.cpp
             ../../shared/cpp/ObjectModel/ParseResult.cpp
             ../../shared/cpp/ObjectModel/ParseUtil.cpp
             ../../shared/cpp/ObjectModel/RichTextBlock.cpp
             ../../shared/cpp/ObjectModel/RichTextElementProperties.cpp
             ../../shared/cpp/ObjectModel/SemanticVersion.cpp
             ../../shared/cpp/ObjectModel/SharedAdaptiveCard.cpp
             ../../shared/cpp/ObjectModel/ShowCardAction.cpp
             ../../shared/cpp/ObjectModel/SubmitAction.cpp
             ../../shared/cpp/ObjectModel/TextBlock.cpp
             ../../shared/cpp/ObjectModel/TextElementProperties.cpp
             ../../shared/cpp/ObjectModel/TextInput.cpp
             ../../shared/cpp/ObjectModel/TextRun.cpp
             ../../shared/cpp/ObjectModel/TimeInput.cpp
             ../../shared/cpp/ObjectModel/ToggleInput.cpp
             ../../shared/cpp/ObjectModel/ToggleVisibilityAction.cpp
             ../../shared/cpp/ObjectModel/ToggleVisibilityTarget.cpp
             ../../shared/cpp/ObjectModel/UnknownElement.cpp
             ../../shared/cpp/ObjectModel/UnknownAction.cpp
             ../../shared/cpp/ObjectModel/Util.cpp
             src/main/cpp/objectmodel_wrap.cpp
             )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       adaptivecards-native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
