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
    
    testApp = [[XCUIApplication alloc] init];
    testApp.launchArguments = [NSArray arrayWithObject:@"ui-testing"];
    [testApp launch];
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
    [self resetTestEnvironment];
    [self openCardForVersion:@"v1.3" forCardType:@"Scenarios" withCardName:@"ActivityUpdateWithLabels.json"];
    
    [self tapOnButtonWithText:@"Set due date"];

    XCUIElementQuery* tables = testApp.tables;
    
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
    [self resetTestEnvironment];
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
    [self resetTestEnvironment];
    [self openCardForVersion:@"v1.3" forCardType:@"Elements" withCardName:@"Input.Text.ErrorMessage.json"];
    
    [self tapOnButtonWithText:@"Submit"];
     
    XCUIElement* chatWindow = testApp.tables[@"ChatWindow"];
    XCUIElement* firstInput = [chatWindow.textFields elementMatchingType:XCUIElementTypeAny identifier:@"Required Input.Text *, This is a required input,"];
    
    XCTAssertTrue([firstInput valueForKey:@"hasKeyboardFocus"], "First input is not selected");
}

- (void)testLongPressAndDragRaiseNoEventInContainers
{
    [self resetTestEnvironment];
    
    [self openCardForVersion:@"v1.5" forCardType:@"Test" withCardName:@"Container.ScrollableSelectableList.json"];
    
    XCUIElement* chatWindow = testApp.tables[@"ChatWindow"];
    
    XCUIElement *container1 = [[chatWindow.cells childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:3];
    
    XCUIElement *container2 = [[chatWindow.cells childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:1];
    
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
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [app launch];
    XCUIElementQuery *tablesQuery = app.tables;
    [tablesQuery /*@START_MENU_TOKEN@*/.staticTexts[@"Input.ChoiceSet.json"] /*[[".cells.staticTexts[@\"Input.ChoiceSet.json\"]",".staticTexts[@\"Input.ChoiceSet.json\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/ tap];
    [/*@START_MENU_TOKEN@*/ [[[app.otherElements[@"ACR Root View"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2].staticTexts[@"Red"] /*[["app","[[[",".scrollViews.otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2]",".cells.staticTexts[@\"Red\"]",".staticTexts[@\"Red\"]",".otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2]"],[[[-1,0,1]],[[1,5,2],[1,2,2]],[[-1,4],[-1,3]]],[0,0,0]]@END_MENU_TOKEN@*/ swipeUp];
    [/*@START_MENU_TOKEN@*/ [[[app.otherElements[@"ACR Root View"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2].staticTexts[@"Blue"] /*[["app","[[[",".scrollViews.otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2]",".cells.staticTexts[@\"Blue\"]",".staticTexts[@\"Blue\"]",".otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2]"],[[[-1,0,1]],[[1,5,2],[1,2,2]],[[-1,4],[-1,3]]],[0,0,0]]@END_MENU_TOKEN@*/ swipeUp];
    [app /*@START_MENU_TOKEN@*/.otherElements[@"ACR Root View"] /*[[".scrollViews.otherElements[@\"ACR Root View\"]",".otherElements[@\"ACR Root View\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/.scrollViews.otherElements.buttons[@"OK"] tap];

    NSDictionary<NSString *, NSString *> *expectedValue = @{
        @"myColor" : @"1",
        @"myColor3" : @"1,3",
        @"myColor2" : @"1",
        @"myColor4" : @"1"
    };
    [self verifyChoiceSetInput:expectedValue application:app];
}

- (void)testCanGatherCorrectValuesFromCompactRadioButton
{
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [app launch];
    XCUIElementQuery *tablesQuery = app.tables;
    [tablesQuery /*@START_MENU_TOKEN@*/.staticTexts[@"Input.ChoiceSet.json"] /*[[".cells.staticTexts[@\"Input.ChoiceSet.json\"]",".staticTexts[@\"Input.ChoiceSet.json\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/ tap];

    XCUIElement *acrRootViewElement = app /*@START_MENU_TOKEN@*/.otherElements[@"ACR Root View"] /*[[".scrollViews.otherElements[@\"ACR Root View\"]",".otherElements[@\"ACR Root View\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/;
    XCUIElement *redStaticText = [[[acrRootViewElement childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:0].staticTexts[@"Red"];

    [redStaticText tap];
    [app /*@START_MENU_TOKEN@*/.otherElements[@"ACR Root View"].tables.pickerWheels[@"Red"] /*[[".scrollViews.otherElements[@\"ACR Root View\"].tables",".cells",".pickers.pickerWheels[@\"Red\"]",".pickerWheels[@\"Red\"]",".otherElements[@\"ACR Root View\"].tables"],[[[-1,4,1],[-1,0,1]],[[-1,3],[-1,2],[-1,1,2]],[[-1,3],[-1,2]]],[0,0]]@END_MENU_TOKEN@*/ swipeUp];
    [app.otherElements[@"ACR Root View"].tables.pickerWheels[@"Blue"] tap];
    [redStaticText tap];
    [acrRootViewElement.scrollViews.otherElements.buttons[@"OK"] tap];

    NSDictionary<NSString *, NSString *> *expectedValue = @{
        @"myColor" : @"3",
        @"myColor3" : @"1,3",
        @"myColor2" : @"1",
        @"myColor4" : @"1"
    };
    [self verifyChoiceSetInput:expectedValue application:app];
}

- (void)testCanGatherCorrectValuesFromExpandedRadioButton
{
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [app launch];

    XCUIElementQuery *tablesQuery = app.tables;
    [tablesQuery /*@START_MENU_TOKEN@*/.staticTexts[@"Input.ChoiceSet.json"] /*[[".cells.staticTexts[@\"Input.ChoiceSet.json\"]",".staticTexts[@\"Input.ChoiceSet.json\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/ tap];

    XCUIElement *greenStaticText = /*@START_MENU_TOKEN@*/ [[[app.otherElements[@"ACR Root View"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:1].staticTexts[@"Green"] /*[["app","[[[",".scrollViews.otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:1]",".cells.staticTexts[@\"Green\"]",".staticTexts[@\"Green\"]",".otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:1]"],[[[-1,0,1]],[[1,5,2],[1,2,2]],[[-1,4],[-1,3]]],[0,0,0]]@END_MENU_TOKEN@*/;
    [greenStaticText tap];
    [/*@START_MENU_TOKEN@*/ [[[app.otherElements[@"ACR Root View"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:1].staticTexts[@"Blue"] /*[["app","[[[",".scrollViews.otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:1]",".cells.staticTexts[@\"Blue\"]",".staticTexts[@\"Blue\"]",".otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:1]"],[[[-1,0,1]],[[1,5,2],[1,2,2]],[[-1,4],[-1,3]]],[0,0,0]]@END_MENU_TOKEN@*/ tap];
    [greenStaticText tap];
    /*@START_MENU_TOKEN@*/ [[[[app.otherElements[@"ACR Root View"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2].staticTexts[@"Red"] swipeLeft]; /*[["app","[[[",".scrollViews.otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2]",".cells.staticTexts[@\"Red\"]","["," swipeUp];"," swipeLeft];",".staticTexts[@\"Red\"]",".otherElements[@\"ACR Root View\"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2]"],[[[-1,0,1]],[[1,8,2],[1,2,2]],[[-1,7,3],[-1,3,3]],[[4,6],[4,5]]],[0,0,0,0]]@END_MENU_TOKEN@*/
    [app /*@START_MENU_TOKEN@*/.otherElements[@"ACR Root View"] /*[[".scrollViews.otherElements[@\"ACR Root View\"]",".otherElements[@\"ACR Root View\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/.scrollViews.otherElements.buttons[@"OK"] tap];

    NSDictionary<NSString *, NSString *> *expectedValue = @{@"myColor" : @"1", @"myColor3" : @"3", @"myColor2" : @"2", @"myColor4" : @"1"};
    [self verifyChoiceSetInput:expectedValue application:app];
}

- (void)testCanGatherCorrectValuesFromChoiceset
{
    // XCUIApplication *app = [[XCUIApplication alloc] init];
    // [app launch];

    XCUIElementQuery *tablesQuery = testApp.tables;
    [tablesQuery /*@START_MENU_TOKEN@*/.staticTexts[@"Input.ChoiceSet.json"] /*[[".cells.staticTexts[@\"Input.ChoiceSet.json\"]",".staticTexts[@\"Input.ChoiceSet.json\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/ tap];

    XCUIElement *acrRootViewElement = testApp /*@START_MENU_TOKEN@*/.otherElements[@"ACR Root View"] /*[[".scrollViews.otherElements[@\"ACR Root View\"]",".otherElements[@\"ACR Root View\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/;
    //[[[[acrRootViewElement childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:4] swipeUp];
    [ [[[testApp.otherElements[@"ACR Root View"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2].staticTexts[@"Red"]  tap];
    [ [[[testApp.otherElements[@"ACR Root View"] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeTable] elementBoundByIndex:2].staticTexts[@"Blue"]  tap];

    XCUIElementQuery *scrollViewsQuery = acrRootViewElement.scrollViews;
    [scrollViewsQuery.otherElements.buttons[@"OK"] tap];

    NSDictionary<NSString *, NSString *> *expectedValue = @{@"myColor" : @"1", @"myColor3" : @"", @"myColor2" : @"1", @"myColor4" : @"1"};
    [self verifyChoiceSetInput:expectedValue application:testApp];
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
