//
//  ACRChoiceSetFilteredStyleViewTests.cpp
//  AdaptiveCardsTests
//
//  Created by Jyoti Kukreja on 26/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRChoiceSetFilteredStyleView.h"
#import "ACRMockViews.h"
#import "ChoiceSetInput.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface ACRChoiceSetFilteredStyleViewTests : XCTestCase

@end

@implementation ACRChoiceSetFilteredStyleViewTests {
    MockACRView *_rootView;
    ACOBaseCardElement *_acoElem;
}

- (void)setUp
{
    _rootView = [[MockACRView alloc] initWithFrame:CGRectMake(0, 0, 20, 30)];
    std::shared_ptr<ChoiceSetInput> choiceSet = std::make_shared<ChoiceSetInput>();
    _acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:choiceSet];
}

- (void)testFilteredStyleViewInit
{
    ACRChoiceSetFilteredStyleView *filteredView = [[ACRChoiceSetFilteredStyleView alloc] initWithInputChoiceSet:_acoElem rootView:_rootView hostConfig:nil searchStateParams:nil typeaheadViewTitle:@"typeahead"];
    XCTAssertNotNil(filteredView.showFilteredListControl);
    NSString *selectedText = [filteredView getSelectedText];
    XCTAssertEqual(selectedText.length, 0);
    BOOL res = [filteredView validate:nil];
    XCTAssertTrue(res);
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [filteredView getInput:dictionary];
    [filteredView updateSelectedChoiceInTextField:@"Option 1"];
    selectedText = [filteredView getSelectedText];
    XCTAssertEqualObjects(selectedText, @"Option 1");
    res = [filteredView validate:nil];
    XCTAssertFalse(res);
}

@end
