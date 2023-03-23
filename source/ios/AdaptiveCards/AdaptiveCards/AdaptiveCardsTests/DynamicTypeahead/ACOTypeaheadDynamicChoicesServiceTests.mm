//
//  ACOTypeaheadDynamicChoicesServiceTests.mm
//  AdaptiveCardsTests
//
//  Created by Jyoti Kukreja on 26/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACRMockViews.h"
#import "ChoiceSetInput.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface ACOTypeaheadDynamicChoicesServiceTests : XCTestCase <ACRTypeaheadSearchProtocol, ACRActionDelegate>

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
    _rootView.acrActionDelegate = self;
    std::shared_ptr<ChoiceSetInput> choiceSet = std::make_shared<ChoiceSetInput>();
    _acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:choiceSet];
    results = [[NSDictionary alloc] init];
    expectation = [self expectationWithDescription:@"dynamicChoicesService"];
}

- (void)testTypeaheadDynamicChoicesService
{
    ACOTypeaheadDynamicChoicesService *dynamicChoicesService = [[ACOTypeaheadDynamicChoicesService alloc] initWithRootView:_rootView inputElem:_acoElem typeaheadSearchDelegate:self];
    XCTAssertEqual(results.count, 0);
    [dynamicChoicesService fetchChoicesFromDynamicSourceWithSearchQuery:@"Microsoft"];
    [self waitForExpectationsWithTimeout:5 handler:nil];
    XCTAssertNotNil(results);
    XCTAssertEqual(results.count, 4);
    XCTAssertTrue(results[@"1"], @"Microsoft1");
    XCTAssertTrue(results[@"2"], @"MicrosoftOffice");
    XCTAssertTrue(results[@"3"], @"MicrosoftWord");
}

- (void)updateTypeaheadUIWithSearchText:(NSString *)searchText dynamicChoices:(NSDictionary *)response withError:(NSError *)error
{
    results = response;
    [expectation fulfill];
}

- (void)onChoiceSetQueryChange:(NSDictionary *)searchRequest acoElem:(ACOBaseCardElement *)elem completion:(void (^)(NSDictionary *response, NSError *error))completion
{
    NSString *queryString = [searchRequest valueForKey:@"value"];
    NSMutableDictionary *responseDict = [[NSMutableDictionary alloc] init];
    NSMutableDictionary *resultsArray = [[NSMutableDictionary alloc] init];
    [responseDict setValue:resultsArray forKey:@"value"];
    [responseDict setValue:@"application/vnd.microsoft.search.searchResponse" forKey:@"type"];
    if ([queryString length]) {
        if ([queryString isEqualToString:@"Microsoft"]) {
            resultsArray[@"1"] = @"Microsoft1";
            resultsArray[@"2"] = @"MicrosoftOffice";
            resultsArray[@"3"] = @"MicrosoftWord";
            resultsArray[@"4"] = @"Microsoftie";
        }
        [responseDict setValue:resultsArray forKey:@"value"];
        completion(responseDict, nil);
        return;
    }
    completion(nil, nil);
}

- (void)didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action
{
}


@end
