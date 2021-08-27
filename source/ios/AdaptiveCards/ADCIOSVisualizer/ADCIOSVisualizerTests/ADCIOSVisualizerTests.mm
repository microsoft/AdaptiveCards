//
//  ADCIOSVisualizerTests.m
//  ADCIOSVisualizerTests
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "AdaptiveCards/ACOAdaptiveCardPrivate.h"
#import "AdaptiveCards/ACOBaseActionElementPrivate.h"
#import "AdaptiveCards/ACOBaseCardElementPrivate.h"
#import "AdaptiveCards/ACOHostConfigPrivate.h"
#import "AdaptiveCards/ACORemoteResourceInformationPrivate.h"
#import "AdaptiveCards/ACRImageProperties.h"
#import "AdaptiveCards/ACRShowCardTarget.h"
#import "AdaptiveCards/ACRViewPrivate.h"
#import "AdaptiveCards/Container.h"
#import "AdaptiveCards/OpenUrlAction.h"
#import "AdaptiveCards/ShowCardAction.h"
#import "AdaptiveCards/SubmitAction.h"
#import "AdaptiveCards/TextBlock.h"
#import "AdaptiveCards/UtiliOS.h"
#import "Adaptivecards/ACRRegistrationPrivate.h"
#import "CustomActionNewType.h"
#import "CustomActionOpenURLRenderer.h"
#import "MockRenderer.h"
#import <AdaptiveCards/ACFramework.h>
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface ADCIOSVisualizerTests : XCTestCase

@end

@implementation ADCIOSVisualizerTests {
    NSBundle *_mainBundle;
    NSString *_defaultHostConfigFile;
    ACOHostConfig *_defaultHostConfig;
    NSSet *_setOfExpectedToFailFiles;
    NSSet *_setOfExcludedFiles;
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

    self.continueAfterFailure = NO;
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

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    _mainBundle = nil;
    _defaultHostConfigFile = nil;
    _defaultHostConfig = nil;
    [[ACRRegistration getInstance] setBaseCardElementRenderer:nil cardElementType:ACRCardElementType::ACRTextBlock];
    [[ACRRegistration getInstance] setBaseCardElementRenderer:nil cardElementType:ACRCardElementType::ACRRichTextBlock];
    [[ACRRegistration getInstance] setBaseCardElementRenderer:nil cardElementType:ACRCardElementType::ACRFactSet];
    [[ACRRegistration getInstance] setBaseCardElementRenderer:nil cardElementType:ACRCardElementType::ACRContainer];
    [[ACRRegistration getInstance] setActionRenderer:nil actionElementType:ACROpenUrl];
    [super tearDown];
}

- (void)testACOBaseActionConversionFromAdaptiveElement
{
    ACOBaseActionElement *acoBaseActionElement = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:nil];
    XCTAssertNil(acoBaseActionElement);

    // Test that the accessibility trait for OpenUrl Action is correctly configured
    std::shared_ptr<OpenUrlAction> openUrlAdaptiveAction = std::make_shared<OpenUrlAction>();
    ACOBaseActionElement *acoOpenUrlActionElement = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:openUrlAdaptiveAction];
    XCTAssertNotNil(acoOpenUrlActionElement);
    XCTAssertTrue(acoOpenUrlActionElement.accessibilityTraits & UIAccessibilityTraitLink);
    XCTAssertFalse(acoOpenUrlActionElement.accessibilityTraits & UIAccessibilityTraitButton);

    // Test that the accessibility trait for Submit Action is correctly configured
    std::shared_ptr<SubmitAction> submitAdaptiveAction = std::make_shared<SubmitAction>();
    ACOBaseActionElement *acoSubmitActionElement = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:submitAdaptiveAction];
    XCTAssertNotNil(acoSubmitActionElement);
    XCTAssertFalse(acoSubmitActionElement.accessibilityTraits & UIAccessibilityTraitLink);
    XCTAssertTrue(acoSubmitActionElement.accessibilityTraits & UIAccessibilityTraitButton);

    // Test that the accessibility trait for Custom Action is correctly configured
    // Image.SelectAction in the iOS test payload contains custom select action json
    NSString *payloadForCustomAction = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Image.SelectAction" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payloadForCustomAction];
    XCTAssertTrue(cardParseResult.isValid);
    std::shared_ptr<AdaptiveCard> adaptiveCard = [cardParseResult.card card];
    std::shared_ptr<Image> adaptiveImage = std::dynamic_pointer_cast<Image>(adaptiveCard->GetBody()[1]);
    XCTAssertTrue(adaptiveImage != nullptr);
    auto adaptiveCustomSelectAction = adaptiveImage->GetSelectAction();

    // register a parser for the custom action json payload
    ACRRegistration *registration = [ACRRegistration getInstance];
    CustomActionNewType *customParser = [[CustomActionNewType alloc] init];
    NSString *keyForNewTyype = @"NewStyle";
    [registration setCustomActionElementParser:customParser key:keyForNewTyype];

    // get the iOS custom action from the adaptive element
    ACOBaseActionElement *acoCustomActionElement = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:adaptiveCustomSelectAction];
    XCTAssertNotNil(acoCustomActionElement);

    // test if the correct accessibility traits are set
    XCTAssertFalse(acoCustomActionElement.accessibilityTraits & UIAccessibilityTraitLink);
    XCTAssertTrue(acoSubmitActionElement.accessibilityTraits & UIAccessibilityTraitButton);

    // render a card for an additonal testing
    ACRRenderResult *renderResult = [ACRRenderer render:cardParseResult.card
                                                 config:nil
                                        widthConstraint:300
                                               delegate:nil];
    XCTAssertTrue(renderResult.succeeded);
    NSObject<ACRSelectActionDelegate> *target;

    // Finally ensure that a target can be built with the custom action by the select action target builder.
    XCTAssertTrue(ACRRenderingStatus::ACROk == buildTarget([renderResult.view getSelectActionsTargetBuilderDirector], acoCustomActionElement, &target));
}

- (void)testRemoteResouceInformation
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"FoodOrder" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];

    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    XCTAssertTrue(cardParseResult.isValid);
    NSArray<ACORemoteResourceInformation *> *remoteInformation = [cardParseResult.card remoteResourceInformation];
    XCTAssertTrue([remoteInformation count] == 3);
    NSArray<NSString *> *testStrings = @[
        @"https://contososcubademo.azurewebsites.net/assets/steak.jpg",
        @"https://contososcubademo.azurewebsites.net/assets/chicken.jpg",
        @"https://contososcubademo.azurewebsites.net/assets/tofu.jpg"
    ];
    unsigned int index = 0;
    for (ACORemoteResourceInformation *info in remoteInformation) {
        XCTAssertTrue([[testStrings objectAtIndex:index++] isEqualToString:info.url.absoluteString]);
        XCTAssertTrue([@"image" isEqualToString:info.mimeType]);
    }
}
/* walk the directories in DFS post-order, and parse and render each payload */
- (void)parseAndRenderDFS:(NSString *)rootPath FileManager:(NSFileManager *)fManager
{
    // files + directories
    NSArray *directoryContents = [fManager contentsOfDirectoryAtPath:rootPath error:nil];
    // files only
    NSMutableArray *filesList = [[NSMutableArray alloc] init];

    // iterate through contents, and if it's a directory, recurse with it, else added to filesList for testing
    for (NSString *path in directoryContents) {
        BOOL isDirectory = NO;
        NSString *resourcePath = [rootPath stringByAppendingPathComponent:path];
        if ([fManager fileExistsAtPath:resourcePath isDirectory:&isDirectory]) {
            NSString *displayName = [fManager displayNameAtPath:path];
            // HostConfigs & Templates directories don't contain valid samples, since there are only two such directories,
            // if condition check for their names are sufficient
            if (isDirectory && !([displayName isEqualToString:@"HostConfig"] or [displayName isEqualToString:@"Templates"])) {
                [self parseAndRenderDFS:resourcePath FileManager:fManager];
            } else if ([[resourcePath pathExtension] isEqualToString:@"json"]) {
                [filesList addObject:resourcePath];
            }
        }
    }

    // testing files in the current directory
    for (NSString *pathToFile in filesList) {
        NSString *payload =
            [NSString stringWithContentsOfFile:pathToFile
                                      encoding:NSUTF8StringEncoding
                                         error:nil];

        NSString *fileName = [pathToFile lastPathComponent];

        ACOAdaptiveCardParseResult *cardParseResult = nil;
        @try {
            if ([_setOfExcludedFiles containsObject:fileName]) {
                continue;
            }
            cardParseResult = [ACOAdaptiveCard fromJson:payload];
            if ([_setOfExpectedToFailFiles containsObject:fileName]) {
                XCTAssertFalse(cardParseResult.isValid);
            } else {
                if (!cardParseResult.isValid) {
                    NSException *e = [NSException exceptionWithName:@"ParseFailed" reason:@"Parsing Failed" userInfo:nil];
                    @throw e;
                }
                XCTAssertTrue(cardParseResult.isValid);
                ACRRenderResult *renderResult;
                @try {
                    renderResult = [ACRRenderer render:cardParseResult.card
                                                config:nil
                                       widthConstraint:300
                                              delegate:nil];
                    XCTAssertTrue(renderResult.succeeded);
                }
                @catch (NSException *exception) {
                    NSLog(@"Render Failed while rendering %@\n%@", fileName, exception);
                    XCTAssertTrue(NO);
                }
            }
        }
        @catch (NSException *exception) {
            NSLog(@"Parsing Failed %@\n%@", fileName, exception);
            XCTAssertTrue(NO);
        }
    }
}
- (void)testParsingAndRenderingAllCards
{
    NSBundle *main = [NSBundle mainBundle];
    NSString *resourcePath = [main resourcePath];
    NSString *rootPath = [resourcePath stringByAppendingPathComponent:@"samples"];
    NSFileManager *fileManager = [NSFileManager defaultManager];

    // testing parsing and rendering from bottom up using DFS
    [self parseAndRenderDFS:rootPath FileManager:fileManager];
}

- (void)testRelativeURLInformation
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Image.ImageBaseUrl" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    XCTAssertTrue(cardParseResult.isValid);
    // host config base url is successfully parsed
    XCTAssertTrue([_defaultHostConfig.baseURL.absoluteString isEqualToString:@"https://pbs.twimg.com/profile_images/3647943215/"]);
}

- (void)testActionTargetBuilderDirectorCanBeBuiltWithNoUserHostconfig
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Feedback" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    XCTAssertTrue(cardParseResult && cardParseResult.isValid);
    ACRRenderResult *renderResult = [ACRRenderer render:cardParseResult.card config:nil widthConstraint:335];
    XCTAssertNotNil([renderResult.view getActionsTargetBuilderDirector]);
}

- (void)testACRTextView
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Feedback" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    XCTAssertTrue(cardParseResult && cardParseResult.isValid);
    ACRRenderResult *renderResult = [ACRRenderer render:cardParseResult.card config:_defaultHostConfig widthConstraint:335];
    NSString *hashkey = @"FeedbackText";
    ACRInputLabelView *acrInputLabelView = (ACRInputLabelView *)[renderResult.view viewWithTag:hashkey.hash];

    XCTAssertNotNil(acrInputLabelView);
    ACRTextView *acrTextView = (ACRTextView *)acrInputLabelView.stack.arrangedSubviews[1];
    XCTAssertTrue([acrTextView.text length] == 0);
}

- (void)testActionSetInputs
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"ActionSet.Inputs.Tests" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    XCTAssertTrue(cardParseResult && cardParseResult.isValid);
    ACRRenderResult *renderResult = [ACRRenderer render:cardParseResult.card config:_defaultHostConfig widthConstraint:335];
    XCTAssertTrue(renderResult && renderResult.succeeded);
    ACOAdaptiveCard *renderedCard = [renderResult.view card];
    NSData *json = [renderedCard inputs];
    NSMutableDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:json options:NSJSONReadingMutableContainers error:nil];
    XCTAssert([dictionary count] == 1);
}

- (void)testActionRegistration
{
    ACRRegistration *registration = [ACRRegistration getInstance];
    // override default Action.OpenUrl renderer
    [registration setActionRenderer:[CustomActionNewTypeRenderer getInstance] actionElementType:ACROpenUrl];
    // make sure it's registered
    XCTAssertEqual([CustomActionNewTypeRenderer getInstance], [registration getActionRendererByType:ACROpenUrl]);
    // reset
    [registration setActionRenderer:nil actionElementType:ACROpenUrl];
    // check the renderer is reset to the default renderer
    XCTAssertEqual([ACRActionOpenURLRenderer getInstance], [registration getActionRendererByType:ACROpenUrl]);
}
// this test ensure that extending text render doesn't crash
// in use case where custom renderer uses default text renderer
- (void)testExtendingTextRenderersDoesNotCrash
{
    ACRRegistration *registration = [ACRRegistration getInstance];
    [registration setBaseCardElementRenderer:[ACRTextBlockRenderer getInstance] cardElementType:ACRCardElementType::ACRTextBlock];
    [registration setBaseCardElementRenderer:[ACRRichTextBlockRenderer getInstance] cardElementType:ACRCardElementType::ACRRichTextBlock];
    [registration setBaseCardElementRenderer:[ACRFactSetRenderer getInstance] cardElementType:ACRCardElementType::ACRFactSet];

    // TextBlock.Maxlines is used for testing when text block renderer is overriden
    // RichTextBlock tests for RichTextBlock renderer extension
    // ActivityUpdate tests TextBlock & FactSet extension combinations
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.MaxLines", @"RichTextBlock", @"ActivityUpdate" ];

    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    for (ACOAdaptiveCard *card in cards) {
        ACRRenderResult *renderResult = [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        XCTAssertNotNil(renderResult.view);
    }
}

- (void)testBuildingShowCardTarget
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Feedback" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    XCTAssertTrue(cardParseResult && cardParseResult.isValid);
    ACRRenderResult *renderResult = [ACRRenderer render:cardParseResult.card config:_defaultHostConfig widthConstraint:335];

    ACRView *testView = renderResult.view;
    std::shared_ptr<AdaptiveCards::TextBlock> textblock = std::make_shared<AdaptiveCards::TextBlock>();
    textblock->SetText("happy testing");

    std::shared_ptr<AdaptiveCards::AdaptiveCard> innerCard = std::make_shared<AdaptiveCards::AdaptiveCard>();
    innerCard->GetBody().push_back(textblock);

    std::shared_ptr<AdaptiveCards::ShowCardAction> action = std::make_shared<AdaptiveCards::ShowCardAction>();
    action->SetCard(innerCard);
    NSObject *target;
    UIButton *button = [UIButton buttonWithType:UIButtonType::UIButtonTypeSystem];
    ACOBaseActionElement *acoAction = [[ACOBaseActionElement alloc] initWithBaseActionElement:action];

    XCTAssert(ACRRenderingStatus::ACRFailed == buildTarget([testView getSelectActionsTargetBuilderDirector], acoAction, &target));

    XCTAssert(ACRRenderingStatus::ACRFailed == buildTarget([testView getQuickReplyTargetBuilderDirector], acoAction, &target));

    // show card target not supported without button
    XCTAssert(ACRRenderingStatus::ACRFailed == buildTarget([testView getActionsTargetBuilderDirector], acoAction, &target));

    XCTAssert(ACRRenderingStatus::ACROk == buildTargetForButton([testView getActionsTargetBuilderDirector], acoAction, button, &target));

    XCTAssertNotNil(target);

    XCTAssertTrue([target respondsToSelector:@selector(createShowCard:superview:)]);
}

- (void)testChoiceSetInputCanGatherDefaultValues
{
    NSString *payload = [NSString stringWithContentsOfFile:[_mainBundle pathForResource:@"Input.ChoiceSet" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
    NSDictionary<NSString *, NSString *> *expectedValue = @{
        @"myColor" : @"1",
        @"myColor3" : @"1,3",
        @"myColor2" : @"1",
        @"myColor1" : @"1",
        @"myColor4" : @"1"
    };
    NSData *expectedData = [NSJSONSerialization dataWithJSONObject:expectedValue options:NSJSONWritingPrettyPrinted error:nil];
    NSString *expectedString = [[NSString alloc] initWithData:expectedData encoding:NSUTF8StringEncoding];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
    XCTAssertTrue(cardParseResult.isValid);
    [ACRRenderer render:cardParseResult.card config:_defaultHostConfig widthConstraint:100.0];
    // manually call input gather function
    NSData *output = [cardParseResult.card inputs];
    NSString *str = [[NSString alloc] initWithData:output encoding:NSUTF8StringEncoding];
    XCTAssertTrue([str isEqualToString:expectedString]);
}

- (void)testMaxActionConfig
{
    ACOHostConfig *config = [[ACOHostConfig alloc] init];
    auto adaptiveConfig = [config getHostConfig];
    ActionsConfig actionConfig;
    actionConfig.maxActions = 2;
    adaptiveConfig->SetActions(actionConfig);
    NSArray<NSString *> *payloadNames = @[ @"Action.ShowCard.Style" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    ACRRenderResult *result = [ACRRenderer render:cards[0] config:config widthConstraint:320.0];
    XCTAssertTrue(result.warnings.count == 1);
    XCTAssertTrue([result.warnings[0].message isEqualToString:@"Some actions were not rendered due to exceeding the maximum number of actions allowed"]);
    actionConfig.maxActions = 3;
    adaptiveConfig->SetActions(actionConfig);
    result = [ACRRenderer render:cards[0] config:config widthConstraint:320.0];
    XCTAssertTrue(result.warnings.count == 0);
}

- (void)testTextPreProcessingFailSafe
{
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.Color" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];

    ACRRegistration *registration = [ACRRegistration getInstance];

    // reset text block renderer registration
    [registration setBaseCardElementRenderer:nil
                             cardElementType:[ACRTextBlockRenderer elemType]];
    // register the text block as a override renderer
    [registration setBaseCardElementRenderer:[ACRTextBlockRenderer getInstance]
                             cardElementType:[ACRTextBlockRenderer elemType]];

    @try {
        ACRRenderResult *result = [ACRRenderer render:cards[0] config:nil widthConstraint:320.0];
        XCTAssertTrue(result.succeeded);
    }
    @catch (NSException *exception) {
        XCTFail(@"intermediate string results should be always available in the text map");
    }
}

- (void)testPerformanceOnComplicatedCards
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"Restaurant", @"FoodOrder", @"ActivityUpdate" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnRestaurant
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"Restaurant" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnFoodOrder
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"FoodOrder" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnActivityUpdate
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"ActivityUpdate" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlock
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.MaxLines", @"TextBlock.Wrap", @"TextBlock.HorizontalAlignment" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockColor
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.Color" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockDateTimeFormatting
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.DateTimeFormatting" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockHorizontalAlignment
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.HorizontalAlignment" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockSubtle
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.IsSubtle" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockLists
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.Lists" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockMarkDown
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.Markdown" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockMaxLines
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.MaxLines" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockSize
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.Size" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockSpacing
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.Spacing" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockWeight
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.Weight" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsTextBlockWrap
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"TextBlock.Wrap" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsImage
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"Image.Size", @"Image.Spacing", @"Image.Style", @"Image" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsColumnSet
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"ColumnSet.Spacing", @"ColumnSet" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testPerformanceOnSimpleCardsColumn
{
    // This is an example of a performance test case.
    NSArray<NSString *> *payloadNames = @[ @"Column.Size.Ratio", @"Column.Spacing", @"Column.Width.Ratio", @"Column.Width", @"Column" ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:payloadNames];
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        for (ACOAdaptiveCard *card in cards) {
            [ACRRenderer render:card config:self->_defaultHostConfig widthConstraint:320.0];
        }
    }];
}

- (void)testSharedEnumsCompatabilityWithiOSSDKEnums
{
    // The below Enums from shared model's numeric values should be in sync with
    // iOS SDK's enum.
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::ActionSet) == ACRActionSet);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::AdaptiveCard) == ACRAdaptiveCard);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::ChoiceInput) == ACRChoiceInput);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::ChoiceSetInput) == ACRChoiceSetInput);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::Column) == ACRColumn);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::ColumnSet) == ACRColumnSet);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::Container) == ACRContainer);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::Custom) == ACRCustom);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::DateInput) == ACRDateInput);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::Fact) == ACRFact);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::FactSet) == ACRFactSet);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::Image) == ACRImage);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::ImageSet) == ACRImageSet);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::Media) == ACRMedia);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::NumberInput) == ACRNumberInput);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::TextBlock) == ACRTextBlock);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::TextInput) == ACRTextInput);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::Table) == ACRTable);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::TableCell) == ACRTableCell);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::TimeInput) == ACRTimeInput);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::ToggleInput) == ACRToggleInput);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::Unknown) == ACRUnknown);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::RichTextBlock) == ACRRichTextBlock);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ActionType::ShowCard) == ACRShowCard);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ActionType::Submit) == ACRSubmit);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ActionType::OpenUrl) == ACROpenUrl);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ActionType::ToggleVisibility) == ACRToggleVisibility);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ContainerStyle::None) == ACRNone);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ContainerStyle::Default) == ACRDefault);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ContainerStyle::Emphasis) == ACREmphasis);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ContainerStyle::Good) == ACRGood);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ContainerStyle::Warning) == ACRWarning);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ContainerStyle::Attention) == ACRAttention);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ContainerStyle::Accent) == ACRAccent);
}

- (void)testACRInputToggleViewCustomRendering
{
    ACRToggleInputView *toggleView = [[ACRToggleInputView alloc] initWithFrame:CGRectMake(0, 0, 50.0f, 100.0f)];
    XCTAssertNotNil(toggleView);
}

- (void)testBackGroundImageNullCheck
{
    renderBackgroundImage(nil, nil, nil);
    XCTAssertTrue(YES);

    auto backgroundImage = BackgroundImage();
    renderBackgroundImage(nil, &backgroundImage, nil, nil);
    XCTAssertTrue(YES);

    UIImageView *imageView = [[UIImageView alloc] init];
    renderBackgroundImage(nil, &backgroundImage, imageView, nil);
    XCTAssertTrue(YES);

    UIImage *image = [UIImage imageNamed:@"Adaptive1.0.png"];
    renderBackgroundImage(nil, &backgroundImage, imageView, image);
    XCTAssertTrue(YES);

    renderBackgroundImage(nil, &backgroundImage, imageView, nil);
    XCTAssertTrue(YES);

    renderBackgroundImage(nil, &backgroundImage, nil, image);
    XCTAssertTrue(YES);
}

// Test that additional property at card level
- (void)testAdditionalPropertiesParsingAtCardLevel
{
    NSArray<NSString *> *payloadNames = @[ @"AdditionalProperties" ];
    ACOAdaptiveCard *iOSCard = [self prepCards:payloadNames][0];
    NSData *additionalProperty = iOSCard.additionalProperty;
    XCTAssertTrue(additionalProperty != nullptr);
    NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:additionalProperty options:NSJSONReadingMutableLeaves error:nil];
    NSNumber *radius = dictionary[@"card.cornerRadius"];
    XCTAssertTrue([radius floatValue] == 50.0f);
}

// Test that additional property is returned as NSData
- (void)testAdditionalPropertiesParsing
{
    NSArray<NSString *> *payloadNames = @[ @"AdditionalProperties" ];
    ACOAdaptiveCard *iOSCard = [self prepCards:payloadNames][0];
    std::shared_ptr<AdaptiveCard> adaptiveCard = [iOSCard card];
    std::shared_ptr<BaseCardElement> adaptiveElement = adaptiveCard->GetBody()[0];
    XCTAssertTrue(adaptiveElement != nullptr);
    ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:adaptiveElement];
    Json::Value blob = adaptiveElement->GetAdditionalProperties();
    NSData *additionalProperty = acoElem.additionalProperty;
    XCTAssertTrue(additionalProperty != nullptr);
    NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:additionalProperty options:NSJSONReadingMutableLeaves error:nil];
    NSNumber *radius = dictionary[@"my.cornerRadius"];
    XCTAssertTrue([radius floatValue] == 20.0f);
}

// Test that empty addtional property is returned as nil
- (void)testAdditionalPropertiesParsingNilValue
{
    NSArray<NSString *> *payloadNames = @[ @"AdditionalProperties" ];
    ACOAdaptiveCard *iOSCard = [self prepCards:payloadNames][0];
    std::shared_ptr<AdaptiveCard> adaptiveCard = [iOSCard card];
    std::shared_ptr<BaseCardElement> adaptiveElement = adaptiveCard->GetBody()[0];
    std::shared_ptr<Container> container = std::dynamic_pointer_cast<Container>(adaptiveElement);
    std::shared_ptr<BaseCardElement> adaptiveTextBlock = container->GetItems()[0];

    ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:adaptiveTextBlock];
    NSData *additionalProperty = acoElem.additionalProperty;
    XCTAssertTrue(additionalProperty == nullptr);
}

// Test that additional property is accessible in the renderer context
- (void)testAdditionalPropertiesRendering
{
    NSArray<NSString *> *payloadNames = @[ @"AdditionalProperties" ];
    ACOAdaptiveCard *iOSCard = [self prepCards:payloadNames][0];
    std::shared_ptr<AdaptiveCard> adaptiveCard = [iOSCard card];
    std::shared_ptr<BaseCardElement> adaptiveElement = adaptiveCard->GetBody()[0];
    ACRRegistration *registration = [ACRRegistration getInstance];
    [registration setBaseCardElementRenderer:[MockRenderer getInstance]
                             cardElementType:ACRContainer];
    [ACRRenderer render:iOSCard
                 config:nil
        widthConstraint:300
               delegate:nil];
}

// Test that overriden default renders can be chosen to use resource resolvers
- (void)testResourceResolverSelectivelyWorksForElements
{
    ACRRegistration *registration = [ACRRegistration getInstance];
    [registration setBaseCardElementRenderer:[MockRenderer getInstance]
                             cardElementType:ACRContainer];
    XCTAssertFalse([registration shouldUseResourceResolverForOverridenDefaultElementRenderers:ACRContainer]);
    [registration setBaseCardElementRenderer:[MockRenderer getInstance] cardElementType:ACRContainer useResourceResolver:YES];
    XCTAssertTrue([registration shouldUseResourceResolverForOverridenDefaultElementRenderers:ACRContainer]);
}

// Test that overriden default renders can be chosen to use resource resolvers
- (void)testResourceResolverSelectivelyWorksForActions
{
    ACRRegistration *registration = [ACRRegistration getInstance];
    [registration setActionRenderer:[CustomActionOpenURLRenderer getInstance] cardElementType:@(ACROpenUrl)];
    XCTAssertFalse([registration shouldUseResourceResolverForOverridenDefaultActionRenderers:ACROpenUrl]);
    [registration setActionRenderer:[CustomActionOpenURLRenderer getInstance] actionElementType:ACROpenUrl useResourceResolver:YES];
    XCTAssertTrue([registration shouldUseResourceResolverForOverridenDefaultActionRenderers:ACROpenUrl]);
}

@end
