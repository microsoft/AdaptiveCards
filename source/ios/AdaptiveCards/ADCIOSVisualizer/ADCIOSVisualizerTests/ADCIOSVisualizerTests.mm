//
//  ADCIOSVisualizerTests.m
//  ADCIOSVisualizerTests
//
//  Created by jwoo on 6/2/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <AdaptiveCards/ACFramework.h>
#import "AdaptiveCards/ACORemoteResourceInformationPrivate.h"


@interface ADCIOSVisualizerTests : XCTestCase

@end

@implementation ADCIOSVisualizerTests
{
    NSBundle *_mainBundle;
    NSString *_defaultHostConfigFile;
    ACOHostConfig *_defaultHostConfig;
}

- (void)setUp {
    [super setUp];
    _mainBundle = [NSBundle mainBundle];
    _defaultHostConfigFile = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"sample" ofType:@"json"]
                              encoding:NSUTF8StringEncoding
                                 error:nil];
    if(_defaultHostConfigFile){
        ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:_defaultHostConfigFile resourceResolvers:nil];
        if(hostconfigParseResult.isValid){
            _defaultHostConfig = hostconfigParseResult.config;
        }
    }
    
    self.continueAfterFailure = NO;
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    _mainBundle = nil;
    _defaultHostConfigFile = nil;
    _defaultHostConfig = nil;
    [super tearDown];
}

- (void)testRemoteResouceInformation {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
 
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"FoodOrder" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    if(cardParseResult.isValid){
        NSArray<ACORemoteResourceInformation *> *remoteInformation = [cardParseResult.card remoteResourceInformation];
        XCTAssertTrue([remoteInformation count] == 3);
        NSArray<NSString *> *testStrings = @[
            @"http://contososcubademo.azurewebsites.net/assets/steak.jpg",
            @"http://contososcubademo.azurewebsites.net/assets/chicken.jpg",
            @"http://contososcubademo.azurewebsites.net/assets/tofu.jpg"
        ];
        unsigned int index = 0;
        for(ACORemoteResourceInformation *info in remoteInformation){
            XCTAssertTrue([[testStrings objectAtIndex:index++] isEqualToString:info.url.absoluteString]);        
            XCTAssertTrue([@"" isEqualToString:info.mimeType]);     
            XCTAssertTrue(ACRImage == info.resourceType);
        }
    }
}

- (void)testRelativeURLInformation {
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Image.ImageBaseUrl" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    if(cardParseResult.isValid){
        // host config base url is successfully parsed
        XCTAssertTrue([_defaultHostConfig.baseURL.absoluteString isEqualToString:@"https://pbs.twimg.com/profile_images/3647943215/"]);
    }
}

- (void)testACRTextView {
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Feedback" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    XCTAssertTrue(cardParseResult && cardParseResult.isValid);
    ACRRenderResult *renderResult = [ACRRenderer render:cardParseResult.card config:_defaultHostConfig widthConstraint:335];
    ACRTextView *acrTextView = (ACRTextView *)[renderResult.view viewWithTag:kACRTextView];
    XCTAssertNotNil(acrTextView);
    XCTAssertTrue([acrTextView.text length] == 0);
}

- (void)testChoiceSetInputCanGatherDefaultValues {
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Input.ChoiceSet" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    NSDictionary<NSString *, NSString *> *expectedValue = @{
        @"myColor" : @"1",
        @"myColor3" : @"1;3",
        @"myColor2" : @"1",
        @"myColor4" : @"1"
        };
    NSData *expectedData = [NSJSONSerialization dataWithJSONObject:expectedValue options:NSJSONWritingPrettyPrinted error:nil];
    NSString *expectedString = [[NSString alloc] initWithData:expectedData encoding:NSUTF8StringEncoding];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    if(cardParseResult.isValid){
        [ACRRenderer render:cardParseResult.card config:_defaultHostConfig widthConstraint:100.0];
        // manually call input gather function
        NSData *output = [cardParseResult.card inputs];
        NSString *str = [[NSString alloc] initWithData:output encoding:NSUTF8StringEncoding];
        XCTAssertTrue([str isEqualToString:expectedString]);
    }
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
