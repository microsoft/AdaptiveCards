//
//  AdaptiveCardsColumnTests.m
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACORenderContext.h"
#import "ACOVisibilityManager.h"
#import "ACRColumnView.h"
#import "ACRSeparator.h"
#import "Column.h"
#import "Enums.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface AdaptiveCardsColumnTests : XCTestCase

@end

@implementation AdaptiveCardsColumnTests

- (void)setUp
{
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
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
    manager.padding = padding;
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
    manager.padding = padding;
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
    manager.padding = padding;
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
    manager.padding = padding;
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

@end
