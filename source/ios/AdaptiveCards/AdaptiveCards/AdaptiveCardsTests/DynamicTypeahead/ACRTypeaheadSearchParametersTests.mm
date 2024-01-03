//
//  ACRTypeaheadSearchParametersTests.cpp
//  AdaptiveCardsTests
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACRTypeaheadSearchParameters.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface ACRTypeaheadSearchParametersTests : XCTestCase

@end

@implementation ACRTypeaheadSearchParametersTests

- (void)testTypeaheadSearchParameterInit
{
    ACRTypeaheadZeroStateParams *zeroStateParams = [[ACRTypeaheadZeroStateParams alloc] initWithtitle:@"Search options" subtitle:nil];
    ACRTypeaheadOfflineStateParams *offlineStateParams = [[ACRTypeaheadOfflineStateParams alloc] initWithtitle:@"the device is offline" subtitle:nil];
    ACRTypeaheadNoResultsStateParams *noResultStateParams = [[ACRTypeaheadNoResultsStateParams alloc] initWithtitle:@"No results" subtitle:nil];
    ACRTypeaheadErrorStateParams *errorStateParams = [[ACRTypeaheadErrorStateParams alloc] initWithtitle:@"Something went wrong" subtitle:nil];
    ACRTypeaheadStateAllParameters *typeaheadParams = [[ACRTypeaheadStateAllParameters alloc] initWithzeroStateParams:zeroStateParams
                                                                                                     errorStateParams:errorStateParams
                                                                                                  noResultStateParams:noResultStateParams
                                                                                                   offlineStateParams:offlineStateParams];
    XCTAssertEqual(zeroStateParams.title, @"Search options");
    XCTAssertEqual(offlineStateParams.title, @"the device is offline");
    XCTAssertEqual(noResultStateParams.title, @"No results");
    XCTAssertEqual(errorStateParams.title, @"Something went wrong");
    XCTAssertNil(zeroStateParams.subtitle);
    XCTAssertNil(offlineStateParams.subtitle);
    XCTAssertNil(noResultStateParams.subtitle);
    XCTAssertNil(errorStateParams.subtitle);
    XCTAssertNotNil(typeaheadParams.zeroStateParams);
    XCTAssertNotNil(typeaheadParams.offlineStateParams);
    XCTAssertNotNil(typeaheadParams.errorStateParams);
    XCTAssertNotNil(typeaheadParams.noResultStateParams);
}

@end
