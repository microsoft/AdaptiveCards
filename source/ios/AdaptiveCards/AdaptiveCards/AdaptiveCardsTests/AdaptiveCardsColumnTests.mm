//
//  AdaptiveCardsColumnTests.m
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCardPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOFillerSpaceManager.h"
#import "ACORenderContext.h"
#import "ACOVisibilityManager.h"
#import "ACRCustomRenderers.h"
#import "ACRRegistration.h"
#import "ACRRenderer.h"
#import "ACRSeparator.h"
#import "ACRView.h"
#import "Column.h"
#import "Enums.h"
#import "Mocks/ACRMockViews.h"
#import "Mocks/ADCMockResolver.h"
#import "TextBlock.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface AdaptiveCardsColumnTests : XCTestCase

@end

@implementation AdaptiveCardsColumnTests {
    NSBundle *_classBundle;
    NSString *_hostConfig;
    NSString *_tearDownMessage;
}

- (void)setUp
{
    _classBundle = [NSBundle bundleForClass:[self class]];
    _hostConfig = [NSString stringWithContentsOfFile:[_classBundle pathForResource:@"sample" ofType:@"json"]
                                            encoding:NSUTF8StringEncoding
                                               error:nil];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    if (self.testRun.failureCount && _tearDownMessage) {
        NSLog(@"%@", _tearDownMessage);
        _tearDownMessage = nil;
    }
}

- (NSArray<ACOAdaptiveCard *> *)prepCards:(NSArray<NSString *> *)fileNames
{
    NSMutableArray<ACOAdaptiveCard *> *cards = [[NSMutableArray alloc] init];
    for (NSString *fileName in fileNames) {
        NSString *payload = [NSString stringWithContentsOfFile:[_classBundle pathForResource:fileName ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];
        ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload];
        XCTAssertTrue(cardParseResult.isValid);
        [cards addObject:cardParseResult.card];
    }
    return cards;
}

- (void)testVisibilityManagerSimple
{
    UIView *viewToBeHidden0 = [[UIView alloc] init];
    ACRMockContentStackView *hostView = [[ACRMockContentStackView alloc] init];
    [hostView addArrangedSubview:viewToBeHidden0];
    ACOVisibilityManager *manager = [hostView getVisibilityManager];
    [manager hideView:viewToBeHidden0 hostView:hostView];
    NSArray<UIView *> *arrangedSubviews = [hostView getArrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    [manager unhideView:viewToBeHidden0 hostView:hostView];
    XCTAssert(arrangedSubviews[0].hidden == NO);
}

- (void)testVisibilityManager
{
    UIView *viewToBeHidden0 = [[UIView alloc] init];
    UIView *viewToBeHidden1 = [[UIView alloc] init];
    ACRSeparator *separator0 = [[ACRSeparator alloc] init];
    ACRMockContentStackView *hostView = [[ACRMockContentStackView alloc] init];
    ACOFillerSpaceManager *fillerSpaceManager = [hostView getFillerSpaceManager];

    [hostView addArrangedSubview:viewToBeHidden0];
    [hostView addArrangedSubview:separator0];
    [hostView addArrangedSubview:viewToBeHidden1];
    [fillerSpaceManager associateSeparatorWithOwnerView:separator0 ownerView:viewToBeHidden1];
    [hostView applyVisibilityToSubviews];

    NSArray<UIView *> *arrangedSubviews = [hostView getArrangedSubviews];
    ACOVisibilityManager *manager = [hostView getVisibilityManager];
    [manager hideView:viewToBeHidden0 hostView:hostView];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    XCTAssert(arrangedSubviews[1].hidden == YES);
    XCTAssert(arrangedSubviews[2].hidden == NO);

    [manager unhideView:viewToBeHidden0 hostView:hostView];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
    XCTAssert(arrangedSubviews[2].hidden == NO);
}

- (void)testVisibilityManagerWithoutSeparator
{
    UIView *viewToBeHidden0 = [[UIView alloc] init];
    UIView *viewToBeHidden1 = [[UIView alloc] init];

    ACRMockContentStackView *hostView = [[ACRMockContentStackView alloc] init];
    ACOVisibilityManager *manager = [hostView getVisibilityManager];
    [hostView addArrangedSubview:viewToBeHidden0];
    [hostView addArrangedSubview:viewToBeHidden1];
    [manager hideView:viewToBeHidden0 hostView:hostView];

    NSArray<UIView *> *arrangedSubviews = [hostView getArrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    XCTAssert(arrangedSubviews[1].hidden == NO);

    [manager unhideView:viewToBeHidden0 hostView:hostView];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
}

- (void)testVisibilityManagerHideLatView
{
    UIView *viewToBeHidden0 = [[UIView alloc] init];
    UIView *viewToBeHidden1 = [[UIView alloc] init];
    ACRSeparator *separator0 = [[ACRSeparator alloc] init];

    ACRMockContentStackView *hostView = [[ACRMockContentStackView alloc] init];
    ACOFillerSpaceManager *fillerSpaceManager = [hostView getFillerSpaceManager];
    ACOVisibilityManager *manager = [hostView getVisibilityManager];

    [hostView addArrangedSubview:viewToBeHidden0];
    [hostView addArrangedSubview:separator0];
    [hostView addArrangedSubview:viewToBeHidden1];

    [fillerSpaceManager associateSeparatorWithOwnerView:separator0 ownerView:viewToBeHidden1];
    [hostView applyVisibilityToSubviews];

    NSArray<UIView *> *arrangedSubviews = [hostView getArrangedSubviews];

    [manager hideView:viewToBeHidden1 hostView:hostView];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == YES);
    XCTAssert(arrangedSubviews[2].hidden == YES);

    [manager unhideView:viewToBeHidden1 hostView:hostView];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
    XCTAssert(arrangedSubviews[2].hidden == NO);
}

- (void)testVisibilityManagerHidePadding
{
    UIView *viewToBeHidden = [[UIView alloc] init];
    ACRMockContentStackView *hostView = [[ACRMockContentStackView alloc] init];
    [hostView addArrangedSubview:viewToBeHidden];

    [hostView configureLayoutAndVisibility:ACRVerticalContentAlignmentTop minHeight:0 heightType:ACRHeightStretch type:ACRContainer];
    NSArray<UIView *> *arrangedSubviews = [hostView getArrangedSubviews];

    // if column width is 'auto' and there isn't a view, padding disapears
    ACOVisibilityManager *manager = [hostView getVisibilityManager];
    [manager hideView:viewToBeHidden hostView:hostView];
    [hostView updatePaddingVisibility];

    XCTAssert(arrangedSubviews[0].hidden == YES);
    XCTAssert(arrangedSubviews[1].hidden == YES);

    [manager unhideView:viewToBeHidden hostView:hostView];
    [hostView updatePaddingVisibility];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
}

- (void)testVisibilityManagerPaddingWithStretch
{
    NSArray<NSString *> *testFiles = @[
        @"Action.ToggleVisibilityExhaustive"
    ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:testFiles];
    ACRRegistration *registration = [ACRRegistration getInstance];
    ACRCustomColumnRenderer *testColumnRenderer = [ACRCustomColumnRenderer getInstance];

    ACOResourceResolvers *resolvers = [[ACOResourceResolvers alloc] init];
    ADCMockResolver *mockReslover = [[ADCMockResolver alloc] init];
    [resolvers setResourceResolver:mockReslover scheme:@"http"];
    [resolvers setResourceResolver:mockReslover scheme:@"https"];
    ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:_hostConfig
                                                            resourceResolvers:resolvers];
    void (^testBlock)(UIView *, NSDictionary *) =
        ^(UIView *view, NSDictionary *dictionary) {
            id val = dictionary[@"expected"][@"numberOfViews"];
            if ([val isKindOfClass:[NSString class]]) {
                int numberOfPaddings = [((NSString *)val) intValue];
                NSUInteger numberOfViews = 0;
                for (UIView *subView in [((ACRColumnView *)view) getArrangedSubviews]) {
                    if (!subView.isHidden) {
                        numberOfViews += 1;
                    }
                }
                XCTAssertEqual(numberOfPaddings, numberOfViews);
            }
        };

    testColumnRenderer.fetchActualRenderedView = testBlock;

    [registration setBaseCardElementRenderer:testColumnRenderer cardElementType:ACRColumn useResourceResolver:YES];

    self.continueAfterFailure = NO;

    for (int i = 0; i < cards.count; i++) {
        ACOAdaptiveCard *card = cards[i];
        _tearDownMessage = [NSString stringWithFormat:@"The number of padding is not correct when tested with %@", testFiles[i]];
        ACRRenderResult *renderResult = [ACRRenderer render:card config:hostconfigParseResult.config widthConstraint:320.0];
        _tearDownMessage = [NSString stringWithFormat:@"rendering failed for %@ card", testFiles[i]];
        XCTAssertEqual(renderResult.succeeded, YES);
    }
}

- (void)testAddColumnToContextNullability
{
    ACORenderContext *context = [[ACORenderContext alloc] init];
    ACRColumnView *columnView = nil;
    UIView *view = [[UIView alloc] init];
    view.tag = 1;
    [context registerVisibilityManager:columnView targetViewTag:view.tag];
    XCTAssertEqual(nil, [context retrieveVisiblityManagerWithTag:view.tag]);
    XCTAssertEqual(nil, [context retrieveVisiblityManagerWithTag:2]);
}

- (void)testAddColumnToContext1
{
    ACORenderContext *context = [[ACORenderContext alloc] init];
    ACRColumnView *columnView = [[ACRColumnView alloc] init];
    UIView *view = [[UIView alloc] init];
    view.tag = 1;
    [context registerVisibilityManager:columnView targetViewTag:view.tag];
    XCTAssertEqual(columnView, [context retrieveVisiblityManagerWithTag:view.tag]);

    UIView *view1 = [[UIView alloc] init];
    view1.tag = 2;
    XCTAssertNotEqual(columnView, [context retrieveVisiblityManagerWithTag:view1.tag]);
}

- (void)testAddColumnToContext2
{
    ACORenderContext *context = [[ACORenderContext alloc] init];
    ACRColumnView *columnView = [[ACRColumnView alloc] init];
    UIView *view = [[UIView alloc] init];
    view.tag = 1;
    [context registerVisibilityManager:columnView targetViewTag:view.tag];
    XCTAssertEqual(columnView, [context retrieveVisiblityManagerWithTag:view.tag]);

    UIView *view1 = [[UIView alloc] init];
    view1.tag = 2;
    [context registerVisibilityManager:columnView targetViewTag:view1.tag];
    XCTAssertEqual(columnView, [context retrieveVisiblityManagerWithTag:view1.tag]);
}

- (void)testPaddingInitialization
{
    ACOFillerSpaceManager *paddingHandler = [[ACOFillerSpaceManager alloc] init];
    XCTAssertNotNil(paddingHandler);
}

- (void)testPaddingConfigurePadding
{
    ACOFillerSpaceManager *paddingHandler = [[ACOFillerSpaceManager alloc] init];
    auto elem = std::make_shared<TextBlock>();
    ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:elem];
    UIView *view = [[UIView alloc] init];
    [paddingHandler configureHeight:view correspondingElement:acoElem];
    XCTAssertEqual(NO, paddingHandler.hasPadding);
    XCTAssertNotEqual(kFillerViewLayoutConstraintPriority, [view contentHuggingPriorityForAxis:UILayoutConstraintAxisVertical]);

    elem->SetHeight(HeightType::Stretch);
    [paddingHandler configureHeight:view correspondingElement:acoElem];
    XCTAssertEqual(YES, paddingHandler.hasPadding);
    XCTAssertEqual(kFillerViewLayoutConstraintPriority, [view contentHuggingPriorityForAxis:UILayoutConstraintAxisVertical]);

    XCTAssertEqual(NO, [paddingHandler isPadding:view]);
}

NSArray<ACOBaseCardElement *> *buildTextBlocksWithHeightStretch(uint n)
{
    NSMutableArray<ACOBaseCardElement *> *textBlocks = [[NSMutableArray alloc] init];
    for (uint i = 0; i < n; i++) {
        auto elem0 = std::make_shared<TextBlock>();
        elem0->SetHeight(HeightType::Stretch);
        ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:elem0];
        [textBlocks addObject:acoElem];
    }

    return textBlocks;
}

- (void)testPaddingActivateConstraints
{
    NSArray<ACOBaseCardElement *> *textBlocks = buildTextBlocksWithHeightStretch(3);
    ACOFillerSpaceManager *paddingHandler = [[ACOFillerSpaceManager alloc] init];
    UIView *superView = [[UIView alloc] init];
    for (ACOBaseCardElement *acoElem in textBlocks) {
        UIView *view = [[UIView alloc] init];
        [superView addSubview:view];
        [paddingHandler configureHeight:view correspondingElement:acoElem];
        XCTAssertFalse([paddingHandler isPadding:view]);
        XCTAssertEqual(kFillerViewLayoutConstraintPriority, [view contentHuggingPriorityForAxis:UILayoutConstraintAxisVertical]);
    }

    NSArray<NSLayoutConstraint *> *constraints = [paddingHandler activateConstraintsForPadding];
    XCTAssertNotNil(constraints);
    XCTAssertEqual(constraints.count, 2);
}

- (void)testPaddingOnSampleCards
{
    NSArray<NSString *> *testFiles = @[
        @"Container.VerticalContentAlignment",
        @"Container.VerticalContentAlignment2",
        @"Column.VerticalAlignment",
        @"ColumnSet.FactSet.VerticalStretch",
        @"ColumnSet.Image.VerticalStretch",
        @"ColumnSet.Input.ChoiceSet.VerticalStretch"
    ];
    NSArray<ACOAdaptiveCard *> *cards = [self prepCards:testFiles];
    ACRRegistration *registration = [ACRRegistration getInstance];
    ACRCustomContainerRenderer *testContainerRenderer = [ACRCustomContainerRenderer getInstance];
    ACRCustomColumnRenderer *testColumnRenderer = [ACRCustomColumnRenderer getInstance];

    ACOResourceResolvers *resolvers = [[ACOResourceResolvers alloc] init];
    ADCMockResolver *mockReslover = [[ADCMockResolver alloc] init];
    [resolvers setResourceResolver:mockReslover scheme:@"http"];
    [resolvers setResourceResolver:mockReslover scheme:@"https"];
    ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:_hostConfig
                                                            resourceResolvers:resolvers];
    void (^testBlock)(UIView *, NSDictionary *) =
        ^(UIView *view, NSDictionary *dictionary) {
            id val = dictionary[@"expected"][@"numberOfViews"];
            if ([val isKindOfClass:[NSString class]]) {
                int numberOfPaddings = [((NSString *)val) intValue];
                NSUInteger numberOfViews = 0;
                for (UIView *subView in [((ACRColumnView *)view) getArrangedSubviews]) {
                    if (!subView.isHidden) {
                        numberOfViews += 1;
                    }
                }
                XCTAssertEqual(numberOfPaddings, numberOfViews);
            }
        };

    testContainerRenderer.fetchActualRenderedView = testBlock;

    testColumnRenderer.fetchActualRenderedView = testBlock;

    [registration setBaseCardElementRenderer:testContainerRenderer cardElementType:ACRContainer useResourceResolver:YES];

    [registration setBaseCardElementRenderer:testColumnRenderer cardElementType:ACRColumn useResourceResolver:YES];

    self.continueAfterFailure = NO;

    for (int i = 0; i < cards.count; i++) {
        ACOAdaptiveCard *card = cards[i];
        _tearDownMessage = [NSString stringWithFormat:@"The number of padding is not correct when tested with %@", testFiles[i]];
        ACRRenderResult *renderResult = [ACRRenderer render:card config:hostconfigParseResult.config widthConstraint:320.0];
        _tearDownMessage = [NSString stringWithFormat:@"rendering failed for %@ card", testFiles[i]];
        XCTAssertEqual(renderResult.succeeded, YES);
    }
}

@end
