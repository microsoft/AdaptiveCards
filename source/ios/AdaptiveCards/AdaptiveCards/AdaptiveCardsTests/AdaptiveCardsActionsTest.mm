//
//  AdaptiveCardsActionsTest.mm
//  AdaptiveCardsActionsTest
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRButton.h"
#import "ACRViewPrivate.h"
#import "BaseActionElement.h"
#import "Mocks/ACRMockViews.h"
#import "Mocks/MockContext.h"
#import "OpenUrlAction.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface AdaptiveCardsActionsTest : XCTestCase

@end

using namespace AdaptiveCards;

@implementation AdaptiveCardsActionsTest {
    MockACRView *_rootView;
}

- (void)setUp
{
    // Put setup code here. This method is called before the invocation of each test method in the class.
    _rootView = [[MockACRView alloc] initWithFrame:CGRectMake(0, 0, 20, 30)];
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (ACOBaseActionElement *)buildSimpleAction
{
    std::shared_ptr<OpenUrlAction> action = std::make_shared<OpenUrlAction>();
    action->SetTitle("Hello");
    action->SetUrl("https://www.bing.com");
    ACOBaseActionElement *acoAction = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:action];
    return acoAction;
}

- (ACRButton *)buildAButton:(ACOBaseActionElement *)acoAction
{
    ACOHostConfig *acoConfig = [[ACOHostConfig alloc] init];
    return (ACRButton *)[ACRButton rootView:_rootView baseActionElement:acoAction title:acoAction.title andHostConfig:acoConfig];
}

- (void)testACRButtonPublicConstraints
{
    ACRButton *button = [self buildAButton:[self buildSimpleAction]];
    XCTAssertNotNil(button);
    XCTAssertNotNil(button.heightConstraint);
    XCTAssertNil(button.titleWidthConstraint);
}

- (void)testACRButtonPublicConstraintsWithImageView
{
    std::string iconURL = "https://adaptivecards.io/content/cats/1.png";
    NSString *iconURLObjc = [NSString stringWithCString:iconURL.c_str() encoding:NSUTF8StringEncoding];
    UIImage *image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:iconURLObjc]]];
    ACOBaseActionElement *action = [self buildSimpleAction];
    action.element->SetIconUrl(iconURL);
    NSString *key = iconURLObjc;
    [_rootView getImageMap][key] = image;
    ACRButton *button = [self buildAButton:action];
    XCTAssertNotNil(button.heightConstraint);
    XCTAssertNotNil(button.titleWidthConstraint);
}

- (void)testACRButtonPublicConstraintsWithImageViewWithKey
{
    std::string iconURL = "https://adaptivecards.io/content/cats/1.png";
    NSString *iconURLObjc = [NSString stringWithCString:iconURL.c_str() encoding:NSUTF8StringEncoding];

    UIImage *image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:iconURLObjc]]];
    UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
    ACOBaseActionElement *acoAction = [self buildSimpleAction];
    acoAction.element->SetIconUrl(iconURL);
    NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)acoAction.element.get()];
    NSString *key = [number stringValue];
    [_rootView setImageView:key view:imageView];
    ACRButton *button = [self buildAButton:acoAction];
    XCTAssertNotNil(button.heightConstraint);
    XCTAssertNotNil(button.titleWidthConstraint);
}

- (void)testACRButtonPublicConstraintsWithIconPlacements
{
    std::string iconURL = "https://adaptivecards.io/content/cats/1.png";
    NSString *iconURLObjc = [NSString stringWithCString:iconURL.c_str() encoding:NSUTF8StringEncoding];

    UIImage *image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:iconURLObjc]]];
    UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
    ACOBaseActionElement *acoAction = [self buildSimpleAction];
    acoAction.element->SetIconUrl(iconURL);
    NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)acoAction.element.get()];
    NSString *key = [number stringValue];
    _rootView.mockContext = [[MockContext alloc] init];
    [_rootView setImageView:key view:imageView];
    [_rootView.mockContext setMockValueForAllHasActionIcons:YES];
    ACRButton *button = [self buildAButton:acoAction];
    XCTAssertNil(button.heightConstraint);
    XCTAssertNil(button.titleWidthConstraint);
}

@end
