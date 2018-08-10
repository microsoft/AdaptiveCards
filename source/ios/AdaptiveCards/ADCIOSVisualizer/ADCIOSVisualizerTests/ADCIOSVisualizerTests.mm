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
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    _mainBundle = nil;
    _defaultHostConfigFile = nil;
    _defaultHostConfig = nil;
    [super tearDown];
}

- (void)testRemoteResouceInformation {
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
        }
        
        for(ACORemoteResourceInformation *info in remoteInformation){
            XCTAssertTrue([@"" isEqualToString:info.mimeType]);
        }
        
        for(ACORemoteResourceInformation *info in remoteInformation){
            XCTAssertTrue(ACRImage == info.resourceType);
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
