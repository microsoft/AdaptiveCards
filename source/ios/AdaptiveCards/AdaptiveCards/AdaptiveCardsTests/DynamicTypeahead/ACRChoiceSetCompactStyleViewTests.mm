//
//  ACRChoiceSetCompactStyleViewTests.mm
//  AdaptiveCardsTests
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOBaseActionElementPrivate.h"
#import "ACOBaseCardElement.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRButton.h"
#import "ACRChoiceSetCompactStyleView.h"
#import "ACRMockViews.h"
#import "ACRViewPrivate.h"
#import "ChoiceSetInput.h"
#import "MockContext.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface ACRChoiceSetCompactStyleViewTests : XCTestCase

@end

using namespace AdaptiveCards;

@implementation ACRChoiceSetCompactStyleViewTests {
    MockACRView *_rootView;
    ACRChoiceSetCompactStyleView *_compactStyleView;
    ACOHostConfig *_hostConfig;
}

- (void)setUp
{
    // Put setup code here. This method is called before the invocation of each test method in the class.
    _rootView = [[MockACRView alloc] initWithFrame:CGRectMake(0, 0, 20, 30)];
    _hostConfig = [[ACOHostConfig alloc] init];
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (ACOBaseCardElement *)buildBaseCardElement
{
    std::shared_ptr<ChoiceSetInput> choiceSet = std::make_shared<ChoiceSetInput>();
    ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:choiceSet];
    return acoElem;
}

- (void)testUpdateFilteredListForStaticTypeahead
{
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init:YES];
    [dataSource addToSource:@"item1"];
    [dataSource addToSource:@"item2"];
    [dataSource addToSource:@"item3"];
    [dataSource addToSource:@"item4"];
    [dataSource updateFilteredListForStaticTypeahead:@"item"];
    XCTAssertEqual(dataSource.count, 4);
    XCTAssertEqual([dataSource getItemAt:0], @"item1");
    XCTAssertEqual([dataSource getItemAt:3], @"item4");
    XCTAssertFalse([dataSource findMatch:@"abcd"]);
    XCTAssertTrue([dataSource findMatch:@"item1"]);
}

- (void)testUpdateFilteredListForDynamicTypeahead
{
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init:YES];
    NSMutableDictionary *requestPayload = [NSMutableDictionary new];
    [requestPayload setDictionary:@{
        @"dynamicChoice1" : @"selected dynamic choice 1",
        @"dynamicChoice2" : @"selected dynamic choice 2",
        @"dynamicChoice3" : @"selected dynamic choice 3",
        @"dynamicChoice4" : @"selected dynamic choice 4",
        @"dynamicChoice5" : @"selected dynamic choice 5"
    }];
    [dataSource updateFilteredListForStaticAndDynamicTypeahead:@"item" dynamicChoices:requestPayload];
    XCTAssertEqual(dataSource.count, 5);
    NSString *choice = [dataSource getItemAt:0];
    XCTAssertEqual(choice, @"dynamicChoice2");
    XCTAssertEqual([dataSource getItemAt:3], @"dynamicChoice4");
    XCTAssertFalse([dataSource findMatch:@"item1"]);
    XCTAssertTrue([dataSource findMatch:@"dynamicChoice1"]);
}

- (void)testMergedStaticAndDynamicFilteredList
{
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init:YES];
    [dataSource addToSource:@"choice1"];
    [dataSource addToSource:@"choice2"];
    [dataSource addToSource:@"Choice3"];
    [dataSource addToSource:@"Choice4"];
    NSMutableDictionary *requestPayload = [NSMutableDictionary new];
    [requestPayload setDictionary:@{
        @"dynamicChoice1" : @"selected dynamic choice 1",
        @"dynamicChoice2" : @"selected dynamic choice 1",
        @"dynamicChoice3" : @"selected dynamic choice 1",
        @"dynamicChoice4" : @"selected dynamic choice 1",
        @"dynamicChoice5" : @"selected dynamic choice 1"
    }];
    [dataSource updateFilteredListForStaticAndDynamicTypeahead:@"Choice" dynamicChoices:requestPayload];
    XCTAssertEqual(dataSource.count, 9);
    XCTAssertEqual([dataSource getItemAt:3], @"dynamicChoice4");
    XCTAssertEqual([dataSource getItemAt:5], @"choice1");
    XCTAssertTrue([dataSource findMatch:@"choice1"]);
    XCTAssertTrue([dataSource findMatch:@"dynamicChoice1"]);
    XCTAssertFalse([dataSource findMatch:@"item"]);
    XCTAssertFalse([dataSource findMatch:@"dynamicChoice"]);
}

- (void)testResetFilter
{
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init:YES];
    [dataSource addToSource:@"item1"];
    [dataSource addToSource:@"item2"];
    [dataSource addToSource:@"item3"];
    [dataSource addToSource:@"item4"];
    XCTAssertEqual(dataSource.count, 4);
    [dataSource resetFilter];
    NSString *item = [dataSource getItemAt:0];
    XCTAssertNotNil(item);
    XCTAssertEqual(dataSource.count, 4);
}

- (void)testGetValueInCompactStyleValidator_DynamicChoices
{
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init:YES];
    ACOBaseCardElement *acoElem = [self buildBaseCardElement];
    ACOChoiceSetFilteredStyleValidator *validator = [[ACOChoiceSetFilteredStyleValidator alloc] init:acoElem dataSource:dataSource];
    NSMutableDictionary *requestPayload = [NSMutableDictionary new];
    [requestPayload setDictionary:@{
        @"dynamicChoice1" : @"selected dynamic choice 1",
        @"dynamicChoice2" : @"selected dynamic choice 2",
        @"dynamicChoice3" : @"selected dynamic choice 3",
        @"dynamicChoice4" : @"selected dynamic choice 4",
        @"dynammicChoice5" : @"selected dynamic choice 5"
    }];
    [validator updateDynamicTitleMap:requestPayload];
    NSString *value = [validator getValue:@"dynamicChoice4"];
    XCTAssertNotNil(value);
    XCTAssertEqual(value, @"selected dynamic choice 4");
}

- (void)testIsValidInCompactStyleValidator
{
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init:YES];
    ACOBaseCardElement *acoElem = [self buildBaseCardElement];
    ACOChoiceSetFilteredStyleValidator *validator = [[ACOChoiceSetFilteredStyleValidator alloc] init:acoElem dataSource:dataSource];
    NSMutableDictionary *requestPayload = [NSMutableDictionary new];
    [requestPayload setDictionary:@{
        @"dynamicChoice1" : @"selected dynamic choice 1",
        @"dynamicChoice2" : @"selected dynamic choice 2",
        @"dynamicChoice3" : @"selected dynamic choice 3",
        @"dynamicChoice4" : @"selected dynamic choice 4",
        @"dynammicChoice5" : @"selected dynamic choice 5"
    }];
    [validator updateDynamicTitleMap:requestPayload];
    XCTAssertTrue([validator isValid:@"dynamicChoice1"]);
    XCTAssertFalse([validator isValid:@"abc"]);
}

@end
