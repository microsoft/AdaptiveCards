//
//  ACRInputTest.m
//  ADCIOSVisualizerTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "AdaptiveCards/ACOAdaptiveCardPrivate.h"
#import "AdaptiveCards/ACOHostConfigPrivate.h"
#import "AdaptiveCards/ACRChoiceSetCompactStyleView.h"
#import <XCTest/XCTest.h>

@interface ACRInputTest : XCTestCase

@end

@implementation ACRInputTest {
    NSBundle *_mainBundle;
    NSString *_defaultHostConfigFile;
    ACOHostConfig *_defaultHostConfig;
    NSSet *_setOfExpectedToFailFiles;
    NSSet *_setOfExcludedFiles;
    NSArray *_testStrings;
    NSArray *_testStrings1;
}

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

    _setOfExpectedToFailFiles = [NSSet setWithArray:@[ @"TypeIsRequired.json", @"AdaptiveCard.MissingVersion.json", @"InvalidMediaMix.json", @"Action.DuplicateIds.json", @"Action.NestedDuplicateIds.json" ]];
    _setOfExcludedFiles = [NSSet setWithArray:@[ @"TooltipTestCard.json" ]];
    _testStrings = @[ @"1", @"2", @"3", @"4", @"5", @"6", @"7", @"8", @"9", @"10" ];
    _testStrings1 = @[ @"apple", @"orange", @"grape", @"banana" ];
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testCanInitFilter
{
    ACOFilteredDataSource *filteredDataSource = [[ACOFilteredDataSource alloc] init];
    XCTAssertNotNil(filteredDataSource);
    XCTAssertTrue(filteredDataSource.count == 0);
}

- (void)testCanAddToFilter
{
    ACOFilteredDataSource *filteredDataSource = [[ACOFilteredDataSource alloc] init];
    XCTAssertNotNil(filteredDataSource);
    XCTAssertTrue(filteredDataSource.count == 0);
    [filteredDataSource addToSource:@"hello"];
    XCTAssertTrue(filteredDataSource.count == 1);
}

- (void)testCanAccessItemInFilter
{
    ACOFilteredDataSource *filteredDataSource = [[ACOFilteredDataSource alloc] init];
    [filteredDataSource addToSource:@"hello"];
    XCTAssertTrue([[filteredDataSource getItemAt:0] isEqualToString:@"hello"]);
}

- (void)testCanAddAllElements
{
    ACOFilteredDataSource *filteredDataSource = [[ACOFilteredDataSource alloc] init];
    for (NSString *key in _testStrings) {
        [filteredDataSource addToSource:key];
    }

    for (NSUInteger i = 0; i < _testStrings.count; i++) {
        XCTAssertTrue([[filteredDataSource getItemAt:i] isEqualToString:[_testStrings objectAtIndex:i]]);
    }
}

- (void)testCanFilterElements
{
    ACOFilteredDataSource *filteredDataSource = [[ACOFilteredDataSource alloc] init];
    for (NSString *key in _testStrings) {
        [filteredDataSource addToSource:key];
    }

    [filteredDataSource filter:@"7"];
    XCTAssertTrue([[filteredDataSource getItemAt:0] isEqualToString:@"7"]);
}

- (void)testCanFilterElements1
{
    ACOFilteredDataSource *filteredDataSource = [[ACOFilteredDataSource alloc] init];
    addDataToFilteredSource(filteredDataSource, _testStrings1);

    [filteredDataSource filter:@"a"];
    XCTAssertEqual(filteredDataSource.count, 4);
    [filteredDataSource filter:@"an"];
    XCTAssertEqual(filteredDataSource.count, 2);
    [filteredDataSource filter:@"ang"];
    XCTAssertEqual(filteredDataSource.count, 1);
}

- (void)testCanInitFilteredViewStateManager
{
    ACOFilteredListStateManager *stateManager = [[ACOFilteredListStateManager alloc] init];
    XCTAssertNotNil(stateManager);
}

- (void)testCanSetFilterListViewState
{
    ACOFilteredListStateManager *stateManager = [[ACOFilteredListStateManager alloc] init];
    [stateManager showFilteredListView];
    XCTAssertTrue(stateManager.isFilteredListVisible);
    [stateManager hideFilteredListView];
    XCTAssertFalse(stateManager.isFilteredListVisible);
}

- (void)testCanSetShowFilterListViewControlState
{
    ACOFilteredListStateManager *stateManager = [[ACOFilteredListStateManager alloc] init];
    [stateManager filteredListControlSelected];
    XCTAssertTrue(stateManager.isShowFilteredListControlSelected);
    [stateManager filteredListControlDeselected];
    XCTAssertFalse(stateManager.isShowFilteredListControlSelected);
}

- (void)testShowFilterListViewControlState
{
    ACOFilteredListStateManager *stateManager = [[ACOFilteredListStateManager alloc] init];
    [stateManager showFilteredListView];
    XCTAssertTrue(stateManager.isShowFilteredListControlSelected);
    [stateManager hideFilteredListView];
    XCTAssertFalse(stateManager.isShowFilteredListControlSelected);
}

- (void)testShowFilterListViewControlState1
{
    ACOFilteredListStateManager *stateManager = [[ACOFilteredListStateManager alloc] init];
    [stateManager filteredListControlSelected];
    XCTAssertTrue(stateManager.isShowFilteredListControlSelected);
    XCTAssertTrue(stateManager.isFilteredListVisible);
    [stateManager filteredListControlDeselected];
    XCTAssertFalse(stateManager.isShowFilteredListControlSelected);
    XCTAssertFalse(stateManager.isFilteredListVisible);
}

- (void)testShowFilterListViewControlState2
{
    ACOFilteredListStateManager *stateManager = [[ACOFilteredListStateManager alloc] init];
    [stateManager showFilteredListView];
    XCTAssertTrue(stateManager.isFilteredListVisible);
    XCTAssertTrue(stateManager.shouldUpdateFilteredList);
    [stateManager showFilteredListView];
    XCTAssertFalse(stateManager.shouldUpdateFilteredList);
    [stateManager showFilteredListView];
    [stateManager showFilteredListView];
    XCTAssertFalse(stateManager.shouldUpdateFilteredList);
    [stateManager hideFilteredListView];
    XCTAssertTrue(stateManager.shouldUpdateFilteredList);
    [stateManager hideFilteredListView];
    XCTAssertFalse(stateManager.shouldUpdateFilteredList);
    [stateManager hideFilteredListView];
    [stateManager hideFilteredListView];
    XCTAssertFalse(stateManager.shouldUpdateFilteredList);
    XCTAssertFalse(stateManager.isFilteredListVisible);
    [stateManager showFilteredListView];
    XCTAssertTrue(stateManager.isFilteredListVisible);
    [stateManager toggleFilteredListView];
    XCTAssertFalse(stateManager.isFilteredListVisible);
    XCTAssertTrue(stateManager.shouldUpdateFilteredList);
}

void addDataToFilteredSource(ACOFilteredDataSource *source, NSArray<NSString *> *data)
{
    for (NSString *key in data) {
        [source addToSource:key];
    }
}

- (void)test0
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Input.ChoiceSet" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    NSDictionary<NSString *, NSString *> *expectedValue = @{
        @"myColor" : @"1",
        @"myColor3" : @"1,3",
        @"myColor2" : @"1",
        @"myColor4" : @"1"
    };
    NSData *expectedData = [NSJSONSerialization dataWithJSONObject:expectedValue options:NSJSONWritingPrettyPrinted error:nil];
    NSString *expectedString = [[NSString alloc] initWithData:expectedData encoding:NSUTF8StringEncoding];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    XCTAssertTrue(cardParseResult.isValid);
    //    [ACRRenderer render:cardParseResult.card config:_defaultHostConfig widthConstraint:100.0];
    //    // manually call input gather function
    //    NSData *output = [cardParseResult.card inputs];
    //    NSString *str = [[NSString alloc] initWithData:output encoding:NSUTF8StringEncoding];
    //    XCTAssertTrue([str isEqualToString:expectedString]);
}


@end
