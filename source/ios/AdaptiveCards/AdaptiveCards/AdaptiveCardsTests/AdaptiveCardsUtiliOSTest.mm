//
//  AdaptiveCardsUtiliOSTest.mm
//  AdaptiveCardsUtiliOSTest
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "UtiliOS.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface AdaptiveCardsUtiliOSTest : XCTestCase

@end

using namespace AdaptiveCards;

@implementation AdaptiveCardsUtiliOSTest

- (void)setUp
{
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testFindTheClosestCGRect0
{
    CGRect rect1 = CGRectMake(0, 0, 500, 500);
    CGRect rect2 = CGRectMake(0, 0, 350, 150);
    CGRect rrect = FindClosestRectToCover(rect1, rect2);
    XCTAssertTrue(abs(rrect.size.width - 350) / 350.0f <= kACRScalerTolerance);
    XCTAssertTrue(abs(rrect.size.height - 350) / 350.0f <= kACRScalerTolerance);
}

- (void)testFindTheClosestCGRect1
{
    CGRect rect1 = CGRectMake(0, 0, 350, 150);
    CGRect rect2 = CGRectMake(0, 0, 350, 150);
    CGRect rrect = FindClosestRectToCover(rect1, rect2);
    XCTAssertTrue(abs(rrect.size.width - 350) / rect2.size.width <= kACRScalerTolerance);
    XCTAssertTrue(abs(rrect.size.height - 150) / rect2.size.height <= kACRScalerTolerance);
}


@end

