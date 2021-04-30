// swift-tools-version:5.4
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "AdaptiveCards",
    platforms: [
        .iOS(.v10)
    ],
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "AdaptiveCards",
            targets: ["AdaptiveCards", "ObjectModel"]),
    ],
    dependencies: [
        // Dependencies declare other packages that this package depends on.
        // .package(url: /* package url */, from: "1.0.0"),
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        .target(
            name: "ObjectModel",
            path: "source/shared/cpp/ObjectModel"
            ),
        .target(
            name: "AdaptiveCards",
            dependencies: ["ObjectModel"],
            path: "source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards",
            exclude: [
                "CMakeLists.txt",
                "CMakeFiles/CMakeOutput.log",
                "testcards/ImageAutoInColumnSet.json",
                "testcards/CustomerCard1.json",
                "cscope.out",
                "cscope.files",
                "Info.plist",
                "testcards/TextBlock.Issue.json",
                "CMakeFiles/cmake.check_cache",
                "cscope.po.out",
                "testcards/TextBlockStrechInColumnSet.json",
                "cscope.in.out",
                "CMakeCache.txt",
                "CMakeFiles/CMakeError.log",
                "CMakeFiles/3.11.1"
            ],
            resources: [
                .process("Images/checked.png"),
                .process("Images/unchecked.png"),
                .process("Images/checked-checkbox-24.png"),
                .process("Images/unchecked-checkbox-24.png")
            ],
            cxxSettings: [CXXSetting.headerSearchPath("../../../../shared/cpp/ObjectModel")],
            linkerSettings:[
                LinkerSetting.linkedFramework("AVFoundation"),
                LinkerSetting.linkedFramework("AVKit"),
                LinkerSetting.linkedFramework("UIKit"),
                LinkerSetting.linkedFramework("CoreGraphics"),
                LinkerSetting.linkedFramework("QuartzCore")
            ]
            )        
    ],
    cxxLanguageStandard: CXXLanguageStandard.cxx17
)
