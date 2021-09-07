//
//  AdaptiveCardsColumnTests.m
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCardPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRRegistration.h"
#import "ACRCustomRenderers.h"
#import "ACOPaddingHandler.h"
#import "ACORenderContext.h"
#import "ACOVisibilityManager.h"
#import "ACRRenderer.h"
#import "ACRSeparator.h"
#import "Mocks/ADCMockResolver.h"
#import "ACRView.h"
#import "Column.h"
#import "Enums.h"
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
    NSMutableArray<UIView *> *arrangedSubviews = [[NSMutableArray alloc] init];
    [arrangedSubviews addObject:viewToBeHidden0];
    ACOVisibilityManager *manager = [[ACOVisibilityManager alloc] init];
    [manager hideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    [manager unhideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == NO);
}

- (void)testVisibilityManager
{
    UIView *viewToBeHidden0 = [[UIView alloc] init];
    UIView *viewToBeHidden1 = [[UIView alloc] init];
    ACRSeparator *separator0 = [[ACRSeparator alloc] init];
    NSMutableArray<UIView *> *arrangedSubviews = [[NSMutableArray alloc] init];
    [arrangedSubviews addObject:viewToBeHidden0];
    [arrangedSubviews addObject:separator0];
    [arrangedSubviews addObject:viewToBeHidden1];
    ACOVisibilityManager *manager = [[ACOVisibilityManager alloc] init];
    [manager hideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    XCTAssert(arrangedSubviews[1].hidden == YES);
    XCTAssert(arrangedSubviews[2].hidden == NO);

    [manager unhideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
    XCTAssert(arrangedSubviews[2].hidden == NO);
}

- (void)testVisibilityManagerWithoutSeparator
{
    UIView *viewToBeHidden0 = [[UIView alloc] init];
    UIView *viewToBeHidden1 = [[UIView alloc] init];
    NSMutableArray<UIView *> *arrangedSubviews = [[NSMutableArray alloc] init];
    [arrangedSubviews addObject:viewToBeHidden0];
    [arrangedSubviews addObject:viewToBeHidden1];

    ACOVisibilityManager *manager = [[ACOVisibilityManager alloc] init];
    [manager hideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    XCTAssert(arrangedSubviews[1].hidden == NO);

    [manager unhideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
}

- (void)testVisibilityManagerHideLatView
{
    UIView *viewToBeHidden0 = [[UIView alloc] init];
    UIView *viewToBeHidden1 = [[UIView alloc] init];
    ACRSeparator *separator0 = [[ACRSeparator alloc] init];
    NSMutableArray<UIView *> *arrangedSubviews = [[NSMutableArray alloc] init];
    [arrangedSubviews addObject:viewToBeHidden0];
    [arrangedSubviews addObject:separator0];
    [arrangedSubviews addObject:viewToBeHidden1];
    ACOVisibilityManager *manager = [[ACOVisibilityManager alloc] init];
    [manager hideView:viewToBeHidden1 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == YES);
    XCTAssert(arrangedSubviews[2].hidden == YES);

    [manager unhideView:viewToBeHidden1 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
    XCTAssert(arrangedSubviews[2].hidden == NO);
}

- (void)testVisibilityManagerHidePadding
{
    UIView *viewToBeHidden = [[UIView alloc] init];
    UIView *padding = [[UIView alloc] init];
    NSMutableArray<UIView *> *arrangedSubviews = [[NSMutableArray alloc] init];
    [arrangedSubviews addObject:viewToBeHidden];
    [arrangedSubviews addObject:padding];
    // if column width is 'auto' and there isn't a view, padding disapears
    ACOVisibilityManager *manager = [[ACOVisibilityManager alloc] init];
    manager.columnWidth = @"auto";
    [manager addPadding:padding];
    [manager hideView:viewToBeHidden arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    XCTAssert(arrangedSubviews[1].hidden == YES);
    [manager unhideView:viewToBeHidden arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
}

- (void)testVisibilityManagerPaddingWithStretch
{
    UIView *viewToBeHidden = [[UIView alloc] init];
    UIView *padding = [[UIView alloc] init];
    NSMutableArray<UIView *> *arrangedSubviews = [[NSMutableArray alloc] init];
    [arrangedSubviews addObject:viewToBeHidden];
    [arrangedSubviews addObject:padding];
    ACOVisibilityManager *manager = [[ACOVisibilityManager alloc] init];
    manager.columnWidth = @"stretch";
    [manager addPadding:padding];
    [manager hideView:viewToBeHidden arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    XCTAssert(arrangedSubviews[1].hidden == NO);
    [manager unhideView:viewToBeHidden arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
}

- (void)testVisibilityManagerDoesNotHidePadding
{
    UIView *viewToBeHidden0 = [[UIView alloc] init];
    ACRSeparator *separator = [[ACRSeparator alloc] init];
    UIView *viewToBeHidden1 = [[UIView alloc] init];
    UIView *padding = [[UIView alloc] init];
    NSMutableArray<UIView *> *arrangedSubviews = [[NSMutableArray alloc] init];
    [arrangedSubviews addObject:viewToBeHidden0];
    [arrangedSubviews addObject:separator];
    [arrangedSubviews addObject:viewToBeHidden1];
    [arrangedSubviews addObject:padding];
    // even if column width is 'auto', if there is a view padding doesn't disapear
    ACOVisibilityManager *manager = [[ACOVisibilityManager alloc] init];
    manager.columnWidth = @"auto";
    [manager addPadding:padding];
    [manager hideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    XCTAssert(arrangedSubviews[1].hidden == YES);
    XCTAssert(arrangedSubviews[2].hidden == NO);
    XCTAssert(arrangedSubviews[3].hidden == NO);
    [manager unhideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
    XCTAssert(arrangedSubviews[2].hidden == NO);
    XCTAssert(arrangedSubviews[3].hidden == NO);
}

- (void)testVisibilityManagerHidePaddingComplex0
{
    UIView *viewToBeHidden0 = [[UIView alloc] init];
    ACRSeparator *separator = [[ACRSeparator alloc] init];
    UIView *viewToBeHidden1 = [[UIView alloc] init];
    UIView *padding = [[UIView alloc] init];
    NSMutableArray<UIView *> *arrangedSubviews = [[NSMutableArray alloc] init];
    [arrangedSubviews addObject:viewToBeHidden0];
    [arrangedSubviews addObject:separator];
    [arrangedSubviews addObject:viewToBeHidden1];
    [arrangedSubviews addObject:padding];
    // even if column width is 'auto', if there is a view padding doesn't disapear
    ACOVisibilityManager *manager = [[ACOVisibilityManager alloc] init];
    manager.columnWidth = @"auto";
    [manager addPadding:padding];
    [manager hideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    [manager hideView:viewToBeHidden1 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == YES);
    XCTAssert(arrangedSubviews[1].hidden == YES);
    XCTAssert(arrangedSubviews[2].hidden == YES);
    XCTAssert(arrangedSubviews[3].hidden == YES);
    [manager unhideView:viewToBeHidden0 arrangedSubviews:arrangedSubviews];
    [manager unhideView:viewToBeHidden1 arrangedSubviews:arrangedSubviews];
    XCTAssert(arrangedSubviews[0].hidden == NO);
    XCTAssert(arrangedSubviews[1].hidden == NO);
    XCTAssert(arrangedSubviews[2].hidden == NO);
    XCTAssert(arrangedSubviews[3].hidden == NO);
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
    ACOPaddingHandler *paddingHandler = [[ACOPaddingHandler alloc] init];
    XCTAssertNotNil(paddingHandler);
}

#if 0
- (void)testPaddingConfigurePadding
{
    ACOPaddingHandler *paddingHandler = [[ACOPaddingHandler alloc] init];
    auto elem = std::make_shared<TextBlock>();
    ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:elem];
    UIView *view = [[UIView alloc] init];
    UIView *padding0 = [paddingHandler configureHeight:view correspondingElement:acoElem];
    XCTAssertNil(padding0);
    
    elem->SetHeight(HeightType::Stretch);
    UIView *padding1 = [paddingHandler configureHeight:view correspondingElement:acoElem];
    
    XCTAssertNotNil(padding1);
}
#endif

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

#if 0
- (void)testPaddingActivateConstraints
{
    NSArray<ACOBaseCardElement *> *textBlocks = buildTextBlocksWithHeightStretch(3);
    ACOPaddingHandler *paddingHandler = [[ACOPaddingHandler alloc] init];
    UIView *superView = [[UIView alloc] init];
    for (ACOBaseCardElement *acoElem in textBlocks) {
        UIView *view = [[UIView alloc] init];
        [superView addSubview:view];
        UIView *padding = [paddingHandler configureHeight:view correspondingElement:acoElem];
        if (padding) {
            [superView addSubview:padding];
        }
        XCTAssertTrue([paddingHandler isPadding:padding]);
        XCTAssertFalse([paddingHandler isPadding:view]);
    }
    
    NSArray<NSLayoutConstraint *> *constraints = [paddingHandler activateConstraintsForPadding];
    XCTAssertNotNil(constraints);
    XCTAssertTrue(constraints.count == 2);
}
#endif

- (void)testPaddingOnSampleCards
{
    NSArray<NSString *> *testFiles = @[@"Container.VerticalContentAlignment",
                                      @"Container.VerticalContentAlignment2",
                                      @"Column.VerticalAlignment",
                                      @"ColumnSet.FactSet.VerticalStretch",
                                      @"ColumnSet.Image.VerticalStretch",
                                      @"ColumnSet.Input.ChoiceSet.VerticalStretch"];
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
    void (^testBlock) (UIView *, NSDictionary *) =
    ^(UIView *view, NSDictionary *dictionary) {
        id val = dictionary[@"expected"][@"numberOfViews"];
        if ([val isKindOfClass:[NSString class]]) {
            int numberOfPaddings = [((NSString *)val) intValue];
            NSUInteger numberOfViews = [((ACRColumnView *)view) getArrangedSubviews].count;
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
