//
//  Action.Execute.m
//  ADCIOSVisualizerTests
//
//  Created by Inyoung Woo on 3/16/21.
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "AdaptiveCards/ACOAuthenticationPrivate.h"
#import "AdaptiveCards/ACOBaseActionElementPrivate.h"
#import "AdaptiveCards/ExecuteAction.h"
#import <AdaptiveCards/AdaptiveCards.h>
#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

@interface Action_Execute : XCTestCase

@end

@implementation Action_Execute {
    NSBundle *_mainBundle;
    NSString *_defaultHostConfigFile;
    ACOHostConfig *_defaultHostConfig;
}

- (void)setUp
{
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
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (NSArray<ACOAdaptiveCard *> *)prepCards:(NSArray<NSString *> *)fileNames
{
    NSMutableArray<ACOAdaptiveCard *> *cards = [[NSMutableArray alloc] init];
    for (NSString *fileName in fileNames) {
        NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:fileName ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
        ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
        XCTAssertTrue(cardParseResult.isValid);
        [cards addObject:cardParseResult.card];
    }
    return cards;
}

- (void)testRefreshWrapper
{
    NSArray<NSString *> *payloadNames = @[ @"Action.Execute" ];
    ACOAdaptiveCard *iOSCard = [self prepCards:payloadNames][0];
    XCTAssertNotNil(iOSCard.refresh);
    // Check UserIds
    XCTAssertNotNil(iOSCard.refresh.userIds);
    XCTAssertTrue([iOSCard.refresh.userIds[0] isEqualToString:@"user1"]);
    XCTAssertTrue([iOSCard.refresh.userIds[1] isEqualToString:@"user2"]);
    XCTAssertTrue([iOSCard.refresh.userIds[2] isEqualToString:@"user3"]);

    // Check Execute Action
    XCTAssertNotNil(iOSCard.refresh.action);
    XCTAssertTrue([iOSCard.refresh.action.verb isEqualToString:@"doStuff"]);

    // Check Action data json
    NSData *data = [iOSCard.refresh.action.data dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableLeaves error:nil];
    XCTAssertTrue([dictionary[@"HereIs"] isEqualToString:@"Some Data"]);
    XCTAssertTrue([dictionary count] == 1);
}

- (void)testRefreshInterface
{
    std::shared_ptr<AdaptiveCards::ExecuteAction> executeAction = std::make_shared<AdaptiveCards::ExecuteAction>();
    executeAction->SetVerb("doStuff");
    const std::string dataString = "{\"HereIs\" :  \"Some Data\"}";
    executeAction->SetDataJson(dataString);
    ACORefresh *refresh = [[ACORefresh alloc] init:[ACOBaseActionElement getACOActionElementFromAdaptiveElement:executeAction] userIds:@[ @"user1", @"user2", @"user3" ]];
    XCTAssertNotNil(refresh);
    // Check UserIds
    XCTAssertNotNil(refresh.userIds);
    XCTAssertTrue([refresh.userIds[0] isEqualToString:@"user1"]);
    XCTAssertTrue([refresh.userIds[1] isEqualToString:@"user2"]);
    XCTAssertTrue([refresh.userIds[2] isEqualToString:@"user3"]);

    // Check Execute Action
    XCTAssertNotNil(refresh.action);
    XCTAssertTrue([refresh.action.verb isEqualToString:@"doStuff"]);

    XCTAssertNotNil(refresh.action.data);
    NSData *data = [refresh.action.data dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableLeaves error:nil];
    XCTAssertTrue([dictionary[@"HereIs"] isEqualToString:@"Some Data"]);
    XCTAssertTrue([dictionary count] == 1);
}

- (void)testAuthWrapper
{
    NSArray<NSString *> *payloadNames = @[ @"Action.Execute.Auth" ];
    ACOAdaptiveCard *iOSCard = [self prepCards:payloadNames][0];
    XCTAssertNotNil(iOSCard.authentication);
    // Authentication
    XCTAssertTrue([iOSCard.authentication.text isEqualToString:@"Please Authenticate"]);
    XCTAssertTrue([iOSCard.authentication.connectionName isEqualToString:@"myConnection"]);

    //// Check the TokenExchangeResource
    XCTAssertNotNil(iOSCard.authentication.tokenExchangeResource);
    XCTAssertTrue([iOSCard.authentication.tokenExchangeResource.Id isEqualToString:@"tokenExchangeId"]);
    XCTAssertTrue([iOSCard.authentication.tokenExchangeResource.uri isEqualToString:@"http:\\token.exchange.resource"]);
    XCTAssertTrue([iOSCard.authentication.tokenExchangeResource.providerId isEqualToString:@"myProvider"]);

    //// Check the button array
    XCTAssertNotNil(iOSCard.authentication.buttons);
    XCTAssertTrue([iOSCard.authentication.buttons[0].type isEqualToString:@"signIn"]);
    XCTAssertTrue([iOSCard.authentication.buttons[0].title isEqualToString:@"Click here to sign in"]);
    XCTAssertTrue([iOSCard.authentication.buttons[0].image isEqualToString:@"http:\\image.uri"]);
    XCTAssertTrue([iOSCard.authentication.buttons[0].value isEqualToString:@"buttonValue"]);
}

- (void)testAuthInterface
{
    ACOTokenExchangeResource *tokenExchangeResource = [[ACOTokenExchangeResource alloc] init:@"tokenExchangeId" uri:@"http:\\token.exchange.resource" providerId:@"myProvider"];
    ACOAuthCardButton *button = [[ACOAuthCardButton alloc] init:@"signIn" title:@"Click here to sign in" image:@"http:\\image.uri" value:@"buttonValue"];
    ACOAuthentication *authentication = [[ACOAuthentication alloc] init:@"Please Authenticate" connectionName:@"myConnection" tokenExchangeResource:tokenExchangeResource buttons:@[ button ]];
    XCTAssertNotNil(authentication);
    // Authentication
    XCTAssertTrue([authentication.text isEqualToString:@"Please Authenticate"]);
    XCTAssertTrue([authentication.connectionName isEqualToString:@"myConnection"]);

    //// Check the TokenExchangeResource
    XCTAssertNotNil(authentication.tokenExchangeResource);
    tokenExchangeResource.Id = @"newId";
    XCTAssertTrue([authentication.tokenExchangeResource.Id isEqualToString:@"tokenExchangeId"]);
    XCTAssertTrue([authentication.tokenExchangeResource.uri isEqualToString:@"http:\\token.exchange.resource"]);
    XCTAssertTrue([authentication.tokenExchangeResource.providerId isEqualToString:@"myProvider"]);

    //// Check the button array
    XCTAssertNotNil(authentication.buttons);
    XCTAssertTrue([authentication.buttons[0].type isEqualToString:@"signIn"]);
    XCTAssertTrue([authentication.buttons[0].title isEqualToString:@"Click here to sign in"]);
    XCTAssertTrue([authentication.buttons[0].image isEqualToString:@"http:\\image.uri"]);
    XCTAssertTrue([authentication.buttons[0].value isEqualToString:@"buttonValue"]);

    button.value = @"newbuttonValue";
    XCTAssertTrue([authentication.buttons[0].value isEqualToString:@"buttonValue"]);
}


@end
