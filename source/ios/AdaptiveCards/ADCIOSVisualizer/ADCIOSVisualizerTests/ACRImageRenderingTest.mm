//
//  ACRImageRenderingTest.m
//  ADCIOSVisualizerTests
//
//  Created by Inyoung Woo on 1/15/21.
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "AdaptiveCards/ACOAdaptiveCardPrivate.h"
#import "AdaptiveCards/ACOBaseActionElementPrivate.h"
#import "AdaptiveCards/ACOBaseCardElementPrivate.h"
#import "AdaptiveCards/ACOHostConfigPrivate.h"
#import "AdaptiveCards/ACRImageProperties.h"
#import "AdaptiveCards/Image.h"
#import "AdaptiveCards/UtiliOS.h"
#import <AdaptiveCards/ACFramework.h>
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface ACRImageRenderingTest : XCTestCase

@end

@implementation ACRImageRenderingTest {
    NSBundle *_mainBundle;
    NSString *_defaultHostConfigFile;
    ACOHostConfig *_defaultHostConfig;
    int configSmallSize;
    int configMediumSize;
    int configLargeSize;
}

typedef struct {
    int pixelWidth;
    int pixelHeight;
    ImageSize size;
    HorizontalAlignment horizontalAlignment;
} TestParam;

typedef void (^validator)(ACRImageProperties *, TestParam);

- (void)setUp
{
    [super setUp];
    _mainBundle = [NSBundle mainBundle];
    _defaultHostConfigFile = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"sample" ofType:@"json"]
                                                       encoding:NSUTF8StringEncoding
                                                          error:nil];
    if (_defaultHostConfigFile) {
        ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:_defaultHostConfigFile resourceResolvers:nil];
        if (hostconfigParseResult.isValid) {
            _defaultHostConfig = hostconfigParseResult.config;
        }
    }

    auto config = [_defaultHostConfig getHostConfig];
    configSmallSize = config->GetImageSizes().smallSize;
    configMediumSize = config->GetImageSizes().mediumSize;
    configLargeSize = config->GetImageSizes().largeSize;

    self.continueAfterFailure = NO;
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testACRImageProperties
{
    std::vector<TestParam> testParams = {
        {.pixelWidth = 0,
         .pixelHeight = 0,
         .size = ImageSize::Small,
         .horizontalAlignment = HorizontalAlignment::Left},
        {.pixelWidth = 20,
         .pixelHeight = 0,
         .size = ImageSize::Auto,
         .horizontalAlignment = HorizontalAlignment::Left},
        {.pixelWidth = 20,
         .pixelHeight = 30,
         .size = ImageSize::Auto,
         .horizontalAlignment = HorizontalAlignment::Left},
        {.pixelWidth = 0,
         .pixelHeight = 0,
         .size = ImageSize::None,
         .horizontalAlignment = HorizontalAlignment::Left},
        {.pixelWidth = 0,
         .pixelHeight = 30,
         .size = ImageSize::None,
         .horizontalAlignment = HorizontalAlignment::Left},
    };

    NSArray<validator> *validators = @[
        ^(ACRImageProperties *imageProperties, TestParam param) {
            XCTAssertTrue(imageProperties.acrImageSize == ACRImageSizeSmall);
            XCTAssertTrue(!imageProperties.isAspectRatioNeeded);
            XCTAssertTrue(CGSizeEqualToSize(imageProperties.contentSize, CGSizeMake(self->configSmallSize, self->configSmallSize)));
        },
        ^(ACRImageProperties *imageProperties, TestParam param) {
            XCTAssertTrue(imageProperties.acrImageSize == ACRImageSizeExplicit);
            XCTAssertTrue(imageProperties.isAspectRatioNeeded);
            XCTAssertTrue(CGSizeEqualToSize(imageProperties.contentSize, CGSizeMake(20, 20)));
        },
        ^(ACRImageProperties *imageProperties, TestParam param) {
            XCTAssertTrue(imageProperties.acrImageSize == ACRImageSizeExplicit);
            XCTAssertTrue(!imageProperties.isAspectRatioNeeded);
            XCTAssertTrue(CGSizeEqualToSize(imageProperties.contentSize, CGSizeMake(20, 30)));
        },
        ^(ACRImageProperties *imageProperties, TestParam param) {
            XCTAssertTrue(imageProperties.acrImageSize == ACRImageSizeAuto);
            XCTAssertTrue(!imageProperties.isAspectRatioNeeded);
            XCTAssertTrue(CGSizeEqualToSize(imageProperties.contentSize, CGSizeMake(0, 0)));
        },
        ^(ACRImageProperties *imageProperties, TestParam param) {
            XCTAssertTrue(imageProperties.acrImageSize == ACRImageSizeExplicit);
            XCTAssertTrue(imageProperties.isAspectRatioNeeded);
            XCTAssertTrue(CGSizeEqualToSize(imageProperties.contentSize, CGSizeMake(30, 30)));
        },
    ];
    [self runValidators:testParams validators:validators];
}

- (void)runValidators:(const std::vector<TestParam> &)testParams validators:(NSArray<validator> *)validators
{
    XCTAssert([validators count] == testParams.size());
    NSInteger i = 0;
    for (auto testParam : testParams) {
        std::shared_ptr<Image> adaptiveImage = std::make_shared<Image>();
        adaptiveImage->SetImageSize(testParam.size);
        adaptiveImage->SetPixelWidth(testParam.pixelWidth);
        adaptiveImage->SetPixelHeight(testParam.pixelHeight);
        adaptiveImage->SetHorizontalAlignment(testParam.horizontalAlignment);
        ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:adaptiveImage];
        ACRImageProperties *imageProperty = [[ACRImageProperties alloc] init:acoElem config:_defaultHostConfig image:nil];
        validators[i](imageProperty, testParam);
        i++;
    }
}

- (void)testACRImageSize
{
    XCTAssertTrue(getACRImageSize(ImageSize::Small, YES) == ACRImageSizeExplicit);
    XCTAssertTrue(getACRImageSize(ImageSize::Small, NO) == ACRImageSizeSmall);
    XCTAssertTrue(getACRImageSize(ImageSize::Medium, YES) == ACRImageSizeExplicit);
    XCTAssertTrue(getACRImageSize(ImageSize::Medium, NO) == ACRImageSizeMedium);
    XCTAssertTrue(getACRImageSize(ImageSize::Large, YES) == ACRImageSizeExplicit);
    XCTAssertTrue(getACRImageSize(ImageSize::Large, NO) == ACRImageSizeLarge);
    XCTAssertTrue(getACRImageSize(ImageSize::Auto, YES) == ACRImageSizeExplicit);
    XCTAssertTrue(getACRImageSize(ImageSize::Auto, NO) == ACRImageSizeAuto);
    XCTAssertTrue(getACRImageSize(ImageSize::Stretch, YES) == ACRImageSizeExplicit);
    XCTAssertTrue(getACRImageSize(ImageSize::Stretch, NO) == ACRImageSizeStretch);
    XCTAssertTrue(getACRImageSize(ImageSize::None, YES) == ACRImageSizeExplicit);
    XCTAssertTrue(getACRImageSize(ImageSize::None, NO) == ACRImageSizeNone);
}

- (void)testACRImagePropertiesWithNullArguments
{
    std::shared_ptr<Image> adaptiveImage = std::make_shared<Image>();
    adaptiveImage->SetUrl("https://bing.com");
    adaptiveImage->SetImageSize(ImageSize::Small);
    ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:adaptiveImage];
    NSArray *imagePropsBuiltWithNilArguments = @[ [[ACRImageProperties alloc] init:nil config:_defaultHostConfig image:nil], [[ACRImageProperties alloc] init:acoElem config:nil image:nil], [[ACRImageProperties alloc] init:nil config:nil image:nil] ];
    // CGSizeZero not available in x86
    CGSize zeroSize = CGSizeMake(0.0f, 0.0f);
    [imagePropsBuiltWithNilArguments enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        ACRImageProperties *imageProperties = (ACRImageProperties *)obj;
        XCTAssertTrue(imageProperties.acrImageSize == ACRImageSizeAuto);
        XCTAssertTrue(imageProperties.acrHorizontalAlignment == ACRLeft);
        XCTAssertTrue(CGSizeEqualToSize(imageProperties.contentSize, zeroSize));
        XCTAssertTrue(imageProperties.pixelWidth == 0);
        XCTAssertTrue(imageProperties.pixelHeight == 0);
        XCTAssertTrue(imageProperties.hasExplicitDimensions == NO);
        XCTAssertTrue(imageProperties.isAspectRatioNeeded == NO);
    }];
}

@end
