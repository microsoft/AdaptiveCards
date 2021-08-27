//
//  ADCIOSVisualizerUITests.m
//  ADCIOSVisualizerUITests
//
//  Created by jwoo on 6/2/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "AdaptiveCards/ACOHostConfigPrivate.h"
#import <AdaptiveCards/ACFramework.h>
#import <XCTest/XCTest.h>
#include <string>

@interface ADCIOSVisualizerUITests : XCTestCase

@end

@implementation ADCIOSVisualizerUITests
{
    XCUIApplication* testApp;
}
    
- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    // In UI tests it is usually best to stop immediately when a failure occurs.
    self.continueAfterFailure = NO;
    // UI tests must launch the application that they test. Doing this in setup will make sure it happens for each test method.
    // In UI tests it’s important to set the initial state - such as interface orientation - required for your tests before they run. The setUp method is a good place to do this.
    
    if (testApp == nil)
    {
        testApp = [[XCUIApplication alloc] init];
        testApp.launchArguments = [NSArray arrayWithObject:@"ui-testing"];
        [testApp launch];
    }
    
    [self resetTestEnvironment];
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)resetTestEnvironment
{
    XCUIElementQuery* buttons = testApp.buttons;
    const int cardDepthLimit = 3;
    
    // try to find Back button and tap it while it appears
    XCUIElement* backButton = buttons[@"Back"];
    
    int backButtonPressedCount = 0;
    while ([backButton exists] && backButtonPressedCount < cardDepthLimit)
    {
        [backButton tap];
        backButton = buttons[@"Back"];
        ++backButtonPressedCount;
    }
    
    // tap on delete all cards button
    [buttons[@"Delete All Cards"] tap];
}

- (void)openCardForVersion:(NSString*)version forCardType:(NSString*)type withCardName:(NSString*)scenarioName
{
    XCUIElementQuery* buttons = testApp.buttons;
    [buttons[version] tap];
    [buttons[type] tap];
    
    XCUIElementQuery* tables = testApp.tables;
    XCUIElement* table = [tables elementBoundByIndex:1];
    XCUIElementQuery* cell = [[table staticTexts] matchingIdentifier:scenarioName];
    
    // Interact with it when visible
    [[cell elementBoundByIndex:0] tap];
}

- (NSDictionary*)parseJsonToDictionary:(NSString*)json
{
    NSData* jsonData = [json dataUsingEncoding:NSUTF8StringEncoding];
    NSError* jsonError;
    NSDictionary* parsedJsonData = [NSJSONSerialization JSONObjectWithData:jsonData
                                                                   options:NSJSONWritingPrettyPrinted
                                                                     error:&jsonError];
    return parsedJsonData;
}

- (NSDictionary*)getInputsFromResultsDictionary:(NSDictionary*)results
{
    return [results objectForKey:@"inputs"];
}

- (NSString*)getInputsString
{
    XCUIElement* resultsTextView = [testApp.staticTexts elementMatchingType:XCUIElementTypeAny identifier:@"SubmitActionRetrievedResults"];
    return resultsTextView.label;
}

- (bool)verifyInputsAreEmpty
{
    return [@" " isEqualToString:[self getInputsString]];
}

- (void)tapOnButtonWithText:(NSString*)buttonText
{
    XCUIElementQuery* buttons = testApp.buttons;
    XCUIElement* button = buttons[buttonText];
    XCTAssertTrue([button exists]);
    [button tap];
}

- (void)verifyInput:(NSString*)inputId matchesExpectedValue:(NSString*)expectedValue inInputSet:(NSDictionary*)inputDictionary
{
    id inputValue = [inputDictionary objectForKey:inputId];
    
    XCTAssertTrue([expectedValue isEqualToString:inputValue], @"Input Id: %@ has value: %@ for expected value: %@", inputId, inputValue, expectedValue);
}

- (void)setDateOnInputDateWithId:(NSString*)Id andLabel:(NSString*)label forYear:(NSString*)year month:(NSString*)month day:(NSString*)day
{
    [self tapOnButtonWithText:Id];
    
    XCUIElement *enterTheDueDateDatePicker = testApp.datePickers[label];
    
    [[enterTheDueDateDatePicker.pickerWheels elementBoundByIndex:0] adjustToPickerWheelValue:month];
    
    [[enterTheDueDateDatePicker.pickerWheels elementBoundByIndex:1] adjustToPickerWheelValue:day];
    
    [[enterTheDueDateDatePicker.pickerWheels elementBoundByIndex:2] adjustToPickerWheelValue:year];
    
    // Dismiss the date picker
    [testApp.toolbars[@"Toolbar"].buttons[@"Done"] tap];
}

- (void)testSmokeTestActivityUpdateDate
{
    [self openCardForVersion:@"v1.3" forCardType:@"Scenarios" withCardName:@"ActivityUpdateWithLabels.json"];
    
    [self tapOnButtonWithText:@"Set due date"];
    
    [self setDateOnInputDateWithId:@"dueDate"
                          andLabel:@"Enter the due date"
                           forYear:@"2021"
                             month:@"July"
                               day:@"15"];
    
    [self tapOnButtonWithText:@"OK"];
        
    NSString* resultsString = [self getInputsString];
    NSDictionary* resultsDictionary = [self parseJsonToDictionary:resultsString];
    NSDictionary* inputs = [self getInputsFromResultsDictionary:resultsDictionary];
    
    [self verifyInput:@"dueDate" matchesExpectedValue:@"2021-07-15" inInputSet:inputs];
}

- (void)testSmokeTestActivityUpdateComment
{
    [self openCardForVersion:@"v1.3" forCardType:@"Scenarios" withCardName:@"ActivityUpdateWithLabels.json"];
    
    XCUIElementQuery* buttons = testApp.buttons;
    [buttons[@"Comment"] tap];

    XCUIElementQuery* tables = testApp.tables;
    XCUIElement* chatWindow = tables[@"ChatWindow"];
    
    XCUIElement* commentTextInput = [chatWindow.textViews elementMatchingType:XCUIElementTypeAny identifier:@"comment"];
    [commentTextInput tap];
    [commentTextInput typeText:@"A comment"];

    [buttons[@"Done"] tap];
    [buttons[@"OK"] tap];

    NSString* resultsString = [self getInputsString];
    NSDictionary* resultsDictionary = [self parseJsonToDictionary:resultsString];
    NSDictionary* inputs = [self getInputsFromResultsDictionary:resultsDictionary];
    
    [self verifyInput:@"comment" matchesExpectedValue:@"A comment" inInputSet:inputs];
}

- (void)testFocusOnValidationFailure
{
    [self openCardForVersion:@"v1.3" forCardType:@"Elements" withCardName:@"Input.Text.ErrorMessage.json"];
    
    [self tapOnButtonWithText:@"Submit"];
     
    XCUIElement* chatWindow = testApp.tables[@"ChatWindow"];
    XCUIElement* firstInput = [chatWindow.textFields elementMatchingType:XCUIElementTypeAny identifier:@"Required Input.Text *, This is a required input,"];
    
    XCTAssertTrue([firstInput valueForKey:@"hasKeyboardFocus"], "First input is not selected");
}

- (void)testLongPressAndDragRaiseNoEventInContainers
{
    [self openCardForVersion:@"v1.5" forCardType:@"Test" withCardName:@"Container.ScrollableSelectableList.json"];
    
    XCUIElement* chatWindow = testApp.tables[@"ChatWindow"];
    
    XCUIElement *container1 = [[chatWindow.cells childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:3];
    
    XCUIElement *container2 = [[chatWindow.cells childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:1];
    
    // For some unknown reason this test succeeds on a mackbook but not in
    // a mac mini (xcode and emulator versions match), so we have to add a
    // small wait time to avoid the long press behaving as a tap
    [NSThread sleepForTimeInterval:1];
    
    // Execute a drag from the 4th element to the 2nd element
    [container1 pressForDuration:1 thenDragToElement:container2];
    
    // assert the submit textview has a blank space, thus the submit event was not raised
    XCTAssert([self verifyInputsAreEmpty]);
}

- (void)verifyChoiceSetInput:(NSDictionary<NSString *, NSString *> *)expectedValue application:(XCUIApplication *)app
{
    NSData *expectedData = [NSJSONSerialization dataWithJSONObject:expectedValue options:NSJSONWritingPrettyPrinted error:nil];
    XCUIElement *queryResult = app.scrollViews.staticTexts[@"ACRUserResponse"];
    NSArray<NSString *> *components = [queryResult.label componentsSeparatedByCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    NSString *stringWithNoWhiteSpaces = [components componentsJoinedByString:@""];
    NSString *expectedString = [[NSString alloc] initWithData:expectedData encoding:NSUTF8StringEncoding];
    NSArray<NSString *> *expectedComponents = [expectedString componentsSeparatedByCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    NSString *expectedStringWithNoWhiteSpaces = [expectedComponents componentsJoinedByString:@""];
    XCTAssertTrue([stringWithNoWhiteSpaces isEqualToString:expectedStringWithNoWhiteSpaces]);
}

- (void)testCanGatherDefaultValuesFromChoiceInputSet
{
    [self openCardForVersion:@"v1.0" forCardType:@"Elements" withCardName:@"Input.ChoiceSet.json"];
        
    XCUIElementQuery* buttons = testApp.buttons;
    [buttons[@"OK"] tap];

    NSString* resultsString = [self getInputsString];
    NSDictionary* resultsDictionary = [self parseJsonToDictionary:resultsString];
    NSDictionary* inputs = [self getInputsFromResultsDictionary:resultsDictionary];
    
    [self verifyInput:@"myColor" matchesExpectedValue:@"1" inInputSet:inputs];
    [self verifyInput:@"myColor2" matchesExpectedValue:@"1" inInputSet:inputs];
    [self verifyInput:@"myColor3" matchesExpectedValue:@"1,3" inInputSet:inputs];
    [self verifyInput:@"myColor4" matchesExpectedValue:@"1" inInputSet:inputs];
}

- (void)testCanGatherCorrectValuesFromCompactChoiceSet
{
    [self openCardForVersion:@"v1.0" forCardType:@"Elements" withCardName:@"Input.ChoiceSet.json"];
    
    XCUIElement* chatWindow = testApp.tables[@"ChatWindow"];
    [chatWindow/*@START_MENU_TOKEN@*/.buttons[@"myColor"]/*[[".cells.buttons[@\"myColor\"]",".buttons[@\"myColor\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/ tap];
    
    XCUIElementQuery *tablesQuery = testApp.tables;
    [tablesQuery.cells[@"(null), Blue"].staticTexts[@"Blue"] tap];
    
    XCUIElementQuery* buttons = testApp.buttons;
    [buttons[@"OK"] tap];

    NSString* resultsString = [self getInputsString];
    NSDictionary* resultsDictionary = [self parseJsonToDictionary:resultsString];
    NSDictionary* inputs = [self getInputsFromResultsDictionary:resultsDictionary];
    
    [self verifyInput:@"myColor" matchesExpectedValue:@"3" inInputSet:inputs];
    [self verifyInput:@"myColor2" matchesExpectedValue:@"1" inInputSet:inputs];
    [self verifyInput:@"myColor3" matchesExpectedValue:@"1,3" inInputSet:inputs];
    [self verifyInput:@"myColor4" matchesExpectedValue:@"1" inInputSet:inputs];
}

- (void)testCanGatherCorrectValuesFromExpandedRadioButton
{
    [self openCardForVersion:@"v1.0" forCardType:@"Elements" withCardName:@"Input.ChoiceSet.json"];
    
    XCUIElement* chatWindow = testApp.tables[@"ChatWindow"];
    [chatWindow.tables[@"myColor2"].staticTexts[@"myColor2, Blue"] tap];
    [chatWindow.tables[@"myColor2"].staticTexts[@"myColor2, Green"] tap];
    [chatWindow/*@START_MENU_TOKEN@*/.tables[@"myColor3"].staticTexts[@"myColor3, Red"]/*[[".cells.tables[@\"myColor3\"]",".cells[@\"Empty list, Red\"]",".staticTexts[@\"Red\"]",".staticTexts[@\"myColor3, Red\"]",".tables[@\"myColor3\"]"],[[[-1,4,1],[-1,0,1]],[[-1,3],[-1,2],[-1,1,2]],[[-1,3],[-1,2]]],[0,0]]@END_MENU_TOKEN@*/ tap];
    
    XCUIElementQuery* buttons = testApp.buttons;
    [buttons[@"OK"] tap];

    NSString* resultsString = [self getInputsString];
    NSDictionary* resultsDictionary = [self parseJsonToDictionary:resultsString];
    NSDictionary* inputs = [self getInputsFromResultsDictionary:resultsDictionary];
    
    [self verifyInput:@"myColor" matchesExpectedValue:@"1" inInputSet:inputs];
    [self verifyInput:@"myColor2" matchesExpectedValue:@"2" inInputSet:inputs];
    [self verifyInput:@"myColor3" matchesExpectedValue:@"3" inInputSet:inputs];
    [self verifyInput:@"myColor4" matchesExpectedValue:@"1" inInputSet:inputs];
}

- (void)testCanGatherCorrectValuesFromChoiceset
{
    [self openCardForVersion:@"v1.0" forCardType:@"Elements" withCardName:@"Input.ChoiceSet.json"];
    
    XCUIElement* chatWindow = testApp.tables[@"ChatWindow"];
    [chatWindow.tables[@"myColor3"].staticTexts[@"myColor3, Blue"] tap];
    [chatWindow/*@START_MENU_TOKEN@*/.tables[@"myColor3"].staticTexts[@"myColor3, Red"]/*[[".cells.tables[@\"myColor3\"]",".cells[@\"Empty list, Red\"]",".staticTexts[@\"Red\"]",".staticTexts[@\"myColor3, Red\"]",".tables[@\"myColor3\"]"],[[[-1,4,1],[-1,0,1]],[[-1,3],[-1,2],[-1,1,2]],[[-1,3],[-1,2]]],[0,0]]@END_MENU_TOKEN@*/ tap];
    
    XCUIElementQuery* buttons = testApp.buttons;
    [buttons[@"OK"] tap];

    NSString* resultsString = [self getInputsString];
    NSDictionary* resultsDictionary = [self parseJsonToDictionary:resultsString];
    NSDictionary* inputs = [self getInputsFromResultsDictionary:resultsDictionary];
    
    [self verifyInput:@"myColor" matchesExpectedValue:@"1" inInputSet:inputs];
    [self verifyInput:@"myColor2" matchesExpectedValue:@"1" inInputSet:inputs];
    [self verifyInput:@"myColor3" matchesExpectedValue:@"" inInputSet:inputs];
    [self verifyInput:@"myColor4" matchesExpectedValue:@"1" inInputSet:inputs];
}

- (void)testHexColorCodeConversion
{
    const std::string testHexColorCode1 = "#FFa", testHexColorCode2 = "#FF123456",
                      testHexColorCode3 = "#FF1234G6", testHexColorCode4 = "#FF12345G",
                      testHexColorCode5 = "#FF1234  ", testHexColorCode6 = "#FF    56",
                      testHexColorCode7 = "   #FF123", testHexColorCode8 = "# FF12345",
                      testHexColorCode9 = "#  FF1234";
    UIColor *color1 = [ACOHostConfig convertHexColorCodeToUIColor:testHexColorCode1];
    XCTAssertTrue(CGColorEqualToColor(color1.CGColor, UIColor.clearColor.CGColor));

    UIColor *color2 = [ACOHostConfig convertHexColorCodeToUIColor:testHexColorCode2];
    XCTAssertTrue(!CGColorEqualToColor(color2.CGColor, UIColor.clearColor.CGColor));

    UIColor *color3 = [ACOHostConfig convertHexColorCodeToUIColor:testHexColorCode3];
    XCTAssertTrue(CGColorEqualToColor(color3.CGColor, UIColor.clearColor.CGColor));

    UIColor *color4 = [ACOHostConfig convertHexColorCodeToUIColor:testHexColorCode4];
    XCTAssertTrue(CGColorEqualToColor(color4.CGColor, UIColor.clearColor.CGColor));

    UIColor *color5 = [ACOHostConfig convertHexColorCodeToUIColor:testHexColorCode5];
    XCTAssertTrue(CGColorEqualToColor(color5.CGColor, UIColor.clearColor.CGColor));

    UIColor *color6 = [ACOHostConfig convertHexColorCodeToUIColor:testHexColorCode6];
    XCTAssertTrue(CGColorEqualToColor(color6.CGColor, UIColor.clearColor.CGColor));

    UIColor *color7 = [ACOHostConfig convertHexColorCodeToUIColor:testHexColorCode7];
    XCTAssertTrue(CGColorEqualToColor(color7.CGColor, UIColor.clearColor.CGColor));

    UIColor *color8 = [ACOHostConfig convertHexColorCodeToUIColor:testHexColorCode8];
    XCTAssertTrue(CGColorEqualToColor(color8.CGColor, UIColor.clearColor.CGColor));

    UIColor *color9 = [ACOHostConfig convertHexColorCodeToUIColor:testHexColorCode9];
    XCTAssertTrue(CGColorEqualToColor(color9.CGColor, UIColor.clearColor.CGColor));
}

@end
