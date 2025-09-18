// swift-tools-version:5.9
import PackageDescription

let package = Package(
    name: "AdaptiveCards",
    defaultLocalization: "en",
    platforms: [
        .iOS(.v14) // Update if you want newer APIs
    ],
    products: [
        .library(
            name: "AdaptiveCards",
            targets: ["AdaptiveCards", "ObjectModel"]),
    ],
    dependencies: [
        // Add any new dependencies here.
    ],
    targets: [
        .target(
            name: "ObjectModel",
            path: "source/shared/cpp/ObjectModel",
            exclude: ["CMakeLists.txt"]
        ),
        .target(
            name: "AdaptiveCards",
            dependencies: ["ObjectModel"],
            path: "source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards",
            exclude: [
                "CMakeLists.txt",
                "Info.plist",
                "testcards/ImageAutoInColumnSet.json",
                "testcards/CustomerCard1.json",
                "testcards/TextBlock.Issue.json",
                "testcards/TextBlockStrechInColumnSet.json"
            ],
            resources: [
                .process("Resources")
            ],
            publicHeadersPath: "include",
            cxxSettings: [
                .headerSearchPath("../../../../shared/cpp/ObjectModel")
            ],
            linkerSettings:[
                .linkedFramework("AVFoundation"),
                .linkedFramework("AVKit"),
                .linkedFramework("UIKit"),
                .linkedFramework("CoreGraphics"),
                .linkedFramework("QuartzCore")
            ]
        ),
        .testTarget(
            name:"AdaptiveCardsTest",
            dependencies: ["ObjectModel", "AdaptiveCards"],
            path:"source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCardsTests",
            resources: [
                .copy("TestFiles")
            ],
            cxxSettings: [
                .headerSearchPath("../../../../shared/cpp/ObjectModel")
            ],
            linkerSettings:[
                .linkedFramework("AVFoundation"),
                .linkedFramework("AVKit"),
                .linkedFramework("UIKit"),
                .linkedFramework("CoreGraphics"),
                .linkedFramework("QuartzCore")
            ]
        )
    ],
    cxxLanguageStandard: .cxx17
)
