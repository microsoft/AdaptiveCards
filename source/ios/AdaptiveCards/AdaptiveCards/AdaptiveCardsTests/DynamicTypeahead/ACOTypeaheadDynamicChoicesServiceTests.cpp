//
//  ACOTypeaheadDynamicChoicesServiceTests.mm
//  AdaptiveCardsTests
//
//  Created by Jyoti Kukreja on 26/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACOBaseCardElement.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRMockViews.h"
#import "ChoiceSetInput.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface ACOTypeaheadDynamicChoicesServiceTests : XCTestCase<ACRTypeaheadSearchProtocol>

@end

@implementation ACOTypeaheadDynamicChoicesServiceTests {
    NSString *searchText;
    XCTestExpectation *expectation;
    MockACRView *_rootView;
    ACOBaseCardElement *_acoElem;
    NSDictionary *results;
}

- (void)setUp
{
    _rootView = [[MockACRView alloc] initWithFrame:CGRectMake(0, 0, 20, 30)];
    std::shared_ptr<ChoiceSetInput> choiceSet = std::make_shared<ChoiceSetInput>();
    _acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:choiceSet];
    results = [[NSDictionary alloc] init];
    expectation = [self expectationWithDescription:@"dynamicChoicesService"];
}

- (void)testTypeaheadDynamicChoicesService
{
    ACOTypeaheadDynamicChoicesService *dynamicChoicesService = [[ACOTypeaheadDynamicChoicesService alloc] initWithRootView:_rootView inputElem:_acoElem typeaheadSearchDelegate:self];
    XCTAssertEqual(results.count,0);
    [dynamicChoicesService fetchChoicesFromDynamicSourceWithSearchQuery:@"microsoft"];
    [self waitForExpectationsWithTimeout:5 handler:nil];
    XCTAssertNil(results);
}

- (void)updateTypeaheadUIWithSearchText:(NSString *)searchText dynamicChoices:(NSDictionary *)response withError:(NSError *)error {
    results = response;
    [expectation fulfill];
}

@end

