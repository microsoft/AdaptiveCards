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

    // Put setup code here. This method is called before the invocation of each test method in the class.
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
        ACORemoteResourceInformation *remoteInformation = [cardParseResult.card remoteResourceInformation];
        std::vector<AdaptiveCards::RemoteResourceInformation> cRemoteResourceInformation = [remoteInformation getRemoteResourceInformations];
        XCTAssertTrue(cRemoteResourceInformation.size() == 3);
        std::vector<std::string> testStrings = {
            "http://contososcubademo.azurewebsites.net/assets/steak.jpg",
            "http://contososcubademo.azurewebsites.net/assets/chicken.jpg",
            "http://contososcubademo.azurewebsites.net/assets/tofu.jpg"
        };
        unsigned int index = 0;
        for(auto remoteResource : cRemoteResourceInformation){
            XCTAssertTrue(testStrings[index++].compare(remoteResource.url) == 0);
        }
    }
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
