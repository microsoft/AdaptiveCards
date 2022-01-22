//
//  ACRImagePropertiesTests.mm
//  ACRImagePropertiesTests
//
//  Copyright © 2022 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRImageProperties.h>
#import <XCTest/XCTest.h>

@interface ACRImagePropertiesTests : XCTestCase

@end

@implementation ACRImagePropertiesTests

- (void)setUp
{
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testConvertToAspectRatioWorksWithZero
{
    CGSize size = CGSizeZero;
    ACRAspectRatio ratio = [ACRImageProperties convertToAspectRatio:size];
    XCTAssert(ratio.widthToHeight == 1.0f);
    XCTAssert(ratio.heightToWidth == 1.0f);
}

- (void)testConvertToAspectRatioWorksWithUninitialized
{
    CGSize randomSize;
    ACRAspectRatio unknownRatio = [ACRImageProperties convertToAspectRatio:randomSize];
    XCTAssert(unknownRatio.heightToWidth > 0);
    XCTAssert(unknownRatio.widthToHeight > 0);
}

- (void)testConvertToAspectRatioWorksWithVeryLargeDenominator
{
    CGSize unreasonableSize = CGSizeMake(10000, 1);
    ACRAspectRatio wellBehavingRatio = [ACRImageProperties convertToAspectRatio:unreasonableSize];
    XCTAssertEqualWithAccuracy(wellBehavingRatio.heightToWidth, 0.01f, 0.01);
    XCTAssertEqual(wellBehavingRatio.widthToHeight, 100);
}

@end
