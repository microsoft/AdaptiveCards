//
//  ADCIOSVisualizerTests.m
//  ADCIOSVisualizerTests
//
//  Created by jwoo on 6/2/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "AdaptiveCards/ACOHostConfigPrivate.h"
#import "AdaptiveCards/ACORemoteResourceInformationPrivate.h"
#import "AdaptiveCards/ACRShowCardTarget.h"
#import "AdaptiveCards/ACRViewPrivate.h"
#import "AdaptiveCards/ShowCardAction.h"
#import "AdaptiveCards/TextBlock.h"
#import "AdaptiveCards/UtiliOS.h"
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
    [super tearDown];
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
        ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];

        if ([_setOfExpectedToFailFiles containsObject:fileName]) {
            XCTAssertFalse(cardParseResult.isValid);
        } else {
            XCTAssertTrue(cardParseResult.isValid);
            ACRRenderResult *renderResult;
            renderResult = [ACRRenderer render:cardParseResult.card
                                        config:nil
                               widthConstraint:300
                                      delegate:nil];
            XCTAssertTrue(renderResult.succeeded);
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
    ACRTextView *acrTextView = (ACRTextView *)[renderResult.view viewWithTag:hashkey.hash];
    XCTAssertNotNil(acrTextView);
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
    XCTAssert([dictionary count] == 2);
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

    XCTAssert(ACRRenderingStatus::ACRFailed == buildTarget([testView getSelectActionsTargetBuilderDirector], action, &target));

    XCTAssert(ACRRenderingStatus::ACRFailed == buildTarget([testView getQuickReplyTargetBuilderDirector], action, &target));

    // show card target not supported without button
    XCTAssert(ACRRenderingStatus::ACRFailed == buildTarget([testView getActionsTargetBuilderDirector], action, &target));

    XCTAssert(ACRRenderingStatus::ACROk == buildTargetForButton([testView getActionsTargetBuilderDirector], action, button, &target));

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
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::TimeInput) == ACRTimeInput);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::ToggleInput) == ACRToggleInput);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::Unknown) == ACRUnknown);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::CardElementType::RichTextBlock) == ACRRichTextBlock);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ActionType::ShowCard) == ACRShowCard);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ActionType::Submit) == ACRSubmit);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ActionType::OpenUrl) == ACROpenUrl);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ActionType::ToggleVisibility) == ACRToggleVisibility);
    XCTAssertTrue(static_cast<int>(AdaptiveCards::ActionType::UnknownAction) == ACRUnknownAction);
}

@end
