cmake_minimum_required (VERSION 3.7)
set(CMAKE_OSX_SYSROOT iphonesimulator11.2)
add_compile_options(-std=c++14 -Wall)
project (AdaptiveCardsLib)
include_directories(../../../../shared/cpp/ObjectModel)
#find_library(UIKIT 
#    UIKit
#    HINTS /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/System/Library/Frameworks/
#    )
#find_library(FOUNDATION Foundation)
#message(STATUS "UIKIT_Library_DIR: ${UIKIT}")
#message(STATUS "Foundation_Library_DIR: ${FOUNDATION}")
#FIND_PATH(UIKIT_INC UIKit/UIKit.h
#    HINTS /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/System/Library/Frameworks/
#    )
#include_directories(${UIKIT_INC})
#message(STATUS "UIKIT_INC: ${UIKIT_INC}")
#message(STATUS "sysroot: ${CMAKE_OSX_DEPLOYMENT_TARGET}")
#MARK_AS_ADVANCED(UIKIT_LIBRARY)
#SET(EXTRA_LIBS ${UIKIT_LIBRARY})

file(GLOB_RECURSE sources ./*.mm ./*.h ./*.m ${UIKIT_INC}/*.h)

#add_library(AdaptiveCardsFramework SHARED ${sources})
#
#set_target_properties(AdaptiveCardsFramework PROPERTIES
#    FRAMEWORK TRUE
#    FRAMEWORK_VERSION A
#    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
#    MACOSX_FRAMEWORK_IDENTIFIER io.adaptivecards
#    )

set(CMAKE_C_FLAGS "-x objective-c -fobjc-arc")
set(CMAKE_CXX_FLAGS "-x objective-c++ -fobjc-arc")
set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa -framework UIKit -framework Foundation -framework SafariServices")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
                     
add_library(adaptiveCards_lib STATIC ${sources})
