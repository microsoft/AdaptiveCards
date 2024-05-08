//
//  ACOTypeaheadDebouncerTests.cpp
//  AdaptiveCardsTests
//
//  Created by Jyoti Kukreja on 26/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOTypeaheadDebouncer.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface ACOTypeaheadDebouncerTests : XCTestCase <ACOTypeaheadDebouncerDelegate>

@end

@implementation ACOTypeaheadDebouncerTests {
    NSString *searchText;
    XCTestExpectation *expectation;
}

- (void)setUp
{
    searchText = @"";
    expectation = [self expectationWithDescription:@"debouncer"];
}

- (void)testTypeaheadDebouncerLogic
{
    ACOTypeaheadDebouncer *debouncer = [[ACOTypeaheadDebouncer alloc] initWithDelay:0.4];
    debouncer.delegate = self;
    XCTAssertEqual(searchText, @"");

    [debouncer postInput:@"test"];
    [self waitForExpectationsWithTimeout:2 handler:nil];
    XCTAssertEqual(searchText, @"microsoft");
}

- (void)debouncerDidSendOutput:(id)output
{
    searchText = @"microsoft";
    [expectation fulfill];
}

@end
