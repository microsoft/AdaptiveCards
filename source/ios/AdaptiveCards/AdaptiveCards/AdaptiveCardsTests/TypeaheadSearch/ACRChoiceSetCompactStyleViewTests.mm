//
//  ACRChoiceSetCompactStyleViewTests.mm
//  AdaptiveCardsTests
//
//  Created by Jyoti Kukreja on 18/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRButton.h"
#import "ACRViewPrivate.h"
#import "ACOBaseCardElement.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRChoiceSetCompactStyleView.h"
#import "ACRMockViews.h"
#import "MockContext.h"
#import "ChoiceSetInput.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface ACRChoiceSetCompactStyleViewTests : XCTestCase

@end

using namespace AdaptiveCards;

@implementation ACRChoiceSetCompactStyleViewTests {
    MockACRView *_rootView;
    ACRChoiceSetCompactStyleView *_compactStyleView;
    ACOHostConfig *_hostConfig;
}

- (void)setUp
{
    // Put setup code here. This method is called before the invocation of each test method in the class.
    _rootView = [[MockACRView alloc] initWithFrame:CGRectMake(0, 0, 20, 30)];
    _hostConfig = [[ACOHostConfig alloc] init];
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (ACOFilteredDataSource *)buildFilteredDataSource
{
    std::shared_ptr<ChoiceSetInput> choiceSet = std::make_shared<ChoiceSetInput>();
    ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:choiceSet];
    ACOFilteredDataSource *dataSource = [[ACOFilteredDataSource alloc] init:YES];
    return dataSource;
}

- (void)testUpdateFilteredListForStaticTypeahead
{
    ACOFilteredDataSource *dataSource = [self buildFilteredDataSource];
    [dataSource addToSource:@"item1"];
    [dataSource addToSource:@"item2"];
    [dataSource addToSource:@"item3"];
    [dataSource addToSource:@"item4"];
    [dataSource updatefilteredListForStaticTypeahead:@"item"];
    XCTAssertEqual(dataSource.count, 4);
    XCTAssertTr(, )
    
}

- (void)testUpdateFilteredListForDynamicTypeahead
{
   
}

- (void)testMereStaticAndDynamicFilteredList
{
    
}

- (void)testResetFilter
{
    
}

@end

