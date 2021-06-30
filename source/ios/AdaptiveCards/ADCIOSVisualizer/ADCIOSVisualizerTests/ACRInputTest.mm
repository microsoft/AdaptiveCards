//
//  ACRInputTest.m
//  ADCIOSVisualizerTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "AdaptiveCards/ACOAdaptiveCardPrivate.h"
#import "AdaptiveCards/ACOBaseCardElementPrivate.h"
#import "AdaptiveCards/ACOHostConfigPrivate.h"
#import "AdaptiveCards/ACRChoiceSetCompactStyleView.h"
#import "AdaptiveCards/ChoiceInput.h"
#import "AdaptiveCards/ChoicesetInput.h"
#import <CoreGraphics/CoreGraphics.h>
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

- (void)testNullFilter
{
    ACOFilteredDataSource *filteredDataSource = [[ACOFilteredDataSource alloc] init:NO];
    XCTAssertNotNil(filteredDataSource);
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
    [stateManager expanded];
    XCTAssertTrue(stateManager.isFilteredListVisible);
    [stateManager collapsed];
    XCTAssertFalse(stateManager.isFilteredListVisible);
}

- (void)testCanSetShowFilterListViewControlState
{
    ACOFilteredListStateManager *stateManager = [[ACOFilteredListStateManager alloc] init];
    [stateManager expanded];
    XCTAssertTrue(stateManager.isShowFilteredListControlSelected);
    [stateManager collapsed];
    XCTAssertFalse(stateManager.isShowFilteredListControlSelected);
}

- (void)testShowFilterListViewControlState1
{
    ACOFilteredListStateManager *stateManager = [[ACOFilteredListStateManager alloc] init];
    [stateManager expanded];
    XCTAssertTrue(stateManager.isShowFilteredListControlSelected);
    XCTAssertTrue(stateManager.isFilteredListVisible);
    [stateManager collapsed];
    XCTAssertFalse(stateManager.isShowFilteredListControlSelected);
    XCTAssertFalse(stateManager.isFilteredListVisible);
}

- (void)testShowFilterListViewControlState2
{
    ACOFilteredListStateManager *stateManager = [[ACOFilteredListStateManager alloc] init];
    [stateManager expanded];
    XCTAssertTrue(stateManager.isFilteredListVisible);
    XCTAssertTrue(stateManager.shouldUpdateFilteredList);
    [stateManager expanded];
    XCTAssertFalse(stateManager.shouldUpdateFilteredList);
    [stateManager expanded];
    [stateManager expanded];
    XCTAssertFalse(stateManager.shouldUpdateFilteredList);
    [stateManager collapsed];
    XCTAssertTrue(stateManager.shouldUpdateFilteredList);
    [stateManager collapsed];
    XCTAssertFalse(stateManager.shouldUpdateFilteredList);
    [stateManager collapsed];
    [stateManager collapsed];
    XCTAssertFalse(stateManager.shouldUpdateFilteredList);
    XCTAssertFalse(stateManager.isFilteredListVisible);
    [stateManager expanded];
    XCTAssertTrue(stateManager.isFilteredListVisible);
    [stateManager toggleState];
    XCTAssertFalse(stateManager.isFilteredListVisible);
    XCTAssertTrue(stateManager.shouldUpdateFilteredList);
}

- (void)testValidation0
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Input.ChoiceSet" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    ACOBaseCardElement *acoElement = [[ACOBaseCardElement alloc] initWithBaseCardElement:[cardParseResult.card card]->GetBody().at(1)];
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init];
    ACOChoiceSetCompactStyleValidator *validator = [[ACOChoiceSetCompactStyleValidator alloc] init:acoElement dataSource:dataSource];
    XCTAssertNotNil(validator);
    XCTAssertTrue([validator isValid:@"Red"]);
}

- (void)testValidation1
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Input.ChoiceSet" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    ACOBaseCardElement *acoElement = [[ACOBaseCardElement alloc] initWithBaseCardElement:[cardParseResult.card card]->GetBody().at(1)];
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init];
    ACOChoiceSetCompactStyleValidator *validator = [[ACOChoiceSetCompactStyleValidator alloc] init:acoElement dataSource:dataSource];

    validator.isRequired = NO;
    XCTAssertTrue([validator isValid:nil]);
    XCTAssertTrue([validator isValid:@""]);

    validator.isRequired = YES;
    XCTAssertFalse([validator isValid:nil]);
    XCTAssertFalse([validator isValid:@""]);
}

- (void)testValidationWithPlaceHolder
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Input.ChoiceSet" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    ACOBaseCardElement *acoElement = [[ACOBaseCardElement alloc] initWithBaseCardElement:[cardParseResult.card card]->GetBody().at(2)];
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init];
    ACOChoiceSetCompactStyleValidator *validator = [[ACOChoiceSetCompactStyleValidator alloc] init:acoElement dataSource:dataSource];

    validator.isRequired = YES;
    XCTAssertFalse([validator isValid:@"Please choose"]);
}

- (void)testGetUserInput
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Input.ChoiceSet" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    ACOBaseCardElement *acoElement = [[ACOBaseCardElement alloc] initWithBaseCardElement:[cardParseResult.card card]->GetBody().at(2)];
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init];
    ACOChoiceSetCompactStyleValidator *validator = [[ACOChoiceSetCompactStyleValidator alloc] init:acoElement dataSource:dataSource];

    validator.isRequired = YES;
    XCTAssertTrue([[validator getValue:@"Please choose"] isEqualToString:@""]);
    XCTAssertTrue([[validator getValue:@""] isEqualToString:@""]);
    XCTAssertTrue([[validator getValue:nil] isEqualToString:@""]);
    XCTAssertTrue([[validator getValue:@"Red"] isEqualToString:@"1"]);
    XCTAssertTrue([[validator getValue:@"Green"] isEqualToString:@"2"]);
    XCTAssertTrue([[validator getValue:@"Blue"] isEqualToString:@"3"]);

    validator.isRequired = NO;
    XCTAssertTrue([[validator getValue:@"Please choose"] isEqualToString:@""]);
    XCTAssertTrue([[validator getValue:@""] isEqualToString:@""]);
    XCTAssertTrue([[validator getValue:nil] isEqualToString:@""]);
    XCTAssertTrue([[validator getValue:@"Red"] isEqualToString:@"1"]);
    XCTAssertTrue([[validator getValue:@"Green"] isEqualToString:@"2"]);
    XCTAssertTrue([[validator getValue:@"Blue"] isEqualToString:@"3"]);
}

- (void)testKeyBoardBoundaryTest
{
    ACOFilteredListLayout *filteredListLayout = [[ACOFilteredListLayout alloc] initWithTopMargin:8.0 bottomMargin:8.0];
    XCTAssertNotNil(filteredListLayout);

    filteredListLayout.keyboardFrame = CGRectZero;

    CGFloat windowHeight = 844.0f;
    CGFloat inputHeight = 34.0f;
    CGFloat yPos = 463.0f;
    XCTAssertFalse([filteredListLayout shouldDrawBelow:windowHeight inputHeight:inputHeight yPos:yPos]);
    yPos = 200.0f;
    XCTAssertTrue([filteredListLayout shouldDrawBelow:windowHeight inputHeight:inputHeight yPos:yPos]);
    yPos = 400.0f;
    XCTAssertTrue([filteredListLayout shouldDrawBelow:windowHeight inputHeight:inputHeight yPos:yPos]);
    filteredListLayout.keyboardFrame = CGRectMake(0, 508, 500, 336);
    //
    //----------------------------
    //|             ||          |
    //|             ||(0, 430)  |
    //|(0, 508)     ||----------|
    //---------------|          |
    // keyboard      |----------|
    //---------------
    // keyboard y dimension 508 <-> 844
    // rootview y dimension 430 <-> 555.33
    // overlap = 555.33 - 508 = 47.33
    yPos = 463.0f;
    CGFloat rootViewHeight = 125.33f;
    CGFloat inputYPos = 25.33f;
    CGRect rootViewFrame = CGRectMake(0, 430, 500, rootViewHeight);
    [filteredListLayout refreshDimension:windowHeight inputYPos:inputYPos inputHeight:inputHeight yPos:yPos rootViewFrame:rootViewFrame];
    XCTAssertEqual((NSInteger)filteredListLayout.height, (NSInteger)(508 - (rootViewFrame.size.height - inputYPos) - filteredListLayout.topMargin - filteredListLayout.bottomMargin));
}

void addDataToFilteredSource(ACOFilteredDataSource *source, NSArray<NSString *> *data)
{
    for (NSString *key in data) {
        [source addToSource:key];
    }
}

@end
