//
//  AdaptiveCardsTests.mm
//  AdaptiveCardsTests
//
//  Created by almedina on 6/22/21.
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRContentHoldingUIView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRRegistration.h"
#import "ACRBaseCardElementRenderer.h"
#import "TextBlock.h"
#import "TextInput.h"
#import "ACRInputLabelView.h"
#import "ACRTextView.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

using namespace AdaptiveCards;

@interface AdaptiveCardsTests : XCTestCase

@end

@implementation AdaptiveCardsTests

- (void)setUp
{
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testTextBlockTextProperty2
{
    std::shared_ptr<AdaptiveCards::TextBlock> textblock = std::make_shared<AdaptiveCards::TextBlock>();
    textblock->SetText("Text test");

    XCTAssert(textblock->GetText() == "Text test");

    std::string serializedTextBlock = textblock->Serialize();
    XCTAssert(serializedTextBlock == "{\"text\":\"Text test\",\"type\":\"TextBlock\"}\n");
}

- (void)testContentHoldingUIViewWithImage
{
    UIImageView *imageView = [[UIImageView alloc] init];
    ACRContentStackView *viewGroup = [[ACRContentStackView alloc] init];
    ACRContentHoldingUIView *wrapperView = [[ACRContentHoldingUIView alloc] initWithImageProperties:[[ACRImageProperties alloc] init] imageView:imageView viewGroup:viewGroup];
    XCTAssertNotNil(wrapperView);
    XCTAssertEqualObjects(wrapperView.contentView, imageView);
}

- (void)testPasswordStyleIsCorrectSet
{
    std::shared_ptr<AdaptiveCards::TextInput> textInput = std::make_shared<AdaptiveCards::TextInput>();
    textInput->SetTextInputStyle(TextInputStyle::Password);
    ACOBaseCardElement *baseCardElement = [[ACOBaseCardElement alloc] initWithBaseCardElement:textInput];
    ACRRegistration *registration = [ACRRegistration getInstance];
    ACRBaseCardElementRenderer *renderer = [registration getRenderer:[NSNumber numberWithInt:ACRTextInput]];
    ACRColumnView *viewGroup = [[ACRColumnView alloc] init];
    ACRView *rootView = [[ACRView alloc] init];
    NSMutableArray *inputs = [[NSMutableArray alloc] init];
    ACOHostConfig *config = [[ACOHostConfig alloc] init];
    UIView *inputView = [renderer render:viewGroup rootView:rootView inputs:inputs
                         baseCardElement:baseCardElement
                              hostConfig:config];
    XCTAssertNotNil(inputView);
    XCTAssertTrue([inputView isKindOfClass:[ACRInputLabelView class]]);
    ACRInputLabelView *labelview = (ACRInputLabelView *)inputView;
    XCTAssertNotNil(labelview.inputView);
    XCTAssertTrue([labelview.inputView isKindOfClass:[UITextField class]]);
    UITextField *textField = (UITextField *)labelview.inputView;
    XCTAssertTrue(textField.isSecureTextEntry);
}

- (void)testInputIsSetToACRTextViewWhenMultiline
{
    std::shared_ptr<AdaptiveCards::TextInput> textInput = std::make_shared<AdaptiveCards::TextInput>();
    textInput->SetIsMultiline(true);
    ACOBaseCardElement *baseCardElement = [[ACOBaseCardElement alloc] initWithBaseCardElement:textInput];
    ACRRegistration *registration = [ACRRegistration getInstance];
    ACRBaseCardElementRenderer *renderer = [registration getRenderer:[NSNumber numberWithInt:ACRTextInput]];
    ACRColumnView *viewGroup = [[ACRColumnView alloc] init];
    ACRView *rootView = [[ACRView alloc] init];
    NSMutableArray *inputs = [[NSMutableArray alloc] init];
    ACOHostConfig *config = [[ACOHostConfig alloc] init];
    UIView *inputView = [renderer render:viewGroup rootView:rootView inputs:inputs
                         baseCardElement:baseCardElement
                              hostConfig:config];
    XCTAssertNotNil(inputView);
    XCTAssertTrue([inputView isKindOfClass:[ACRInputLabelView class]]);
    ACRInputLabelView *labelview = (ACRInputLabelView *)inputView;
    XCTAssertNotNil(labelview.inputView);
    XCTAssertTrue([labelview.inputView isKindOfClass:[ACRTextView class]]);
}

- (void)testInputIsSetToACRTextFieldWhenMultilineAndPasswordStyleAreSet
{
    std::shared_ptr<AdaptiveCards::TextInput> textInput = std::make_shared<AdaptiveCards::TextInput>();
    textInput->SetIsMultiline(true);
    textInput->SetTextInputStyle(TextInputStyle::Password);
    ACOBaseCardElement *baseCardElement = [[ACOBaseCardElement alloc] initWithBaseCardElement:textInput];
    ACRRegistration *registration = [ACRRegistration getInstance];
    ACRBaseCardElementRenderer *renderer = [registration getRenderer:[NSNumber numberWithInt:ACRTextInput]];
    ACRColumnView *viewGroup = [[ACRColumnView alloc] init];
    ACRView *rootView = [[ACRView alloc] init];
    NSMutableArray *inputs = [[NSMutableArray alloc] init];
    ACOHostConfig *config = [[ACOHostConfig alloc] init];
    UIView *inputView = [renderer render:viewGroup rootView:rootView inputs:inputs
                         baseCardElement:baseCardElement
                              hostConfig:config];
    XCTAssertNotNil(inputView);
    XCTAssertTrue([inputView isKindOfClass:[ACRInputLabelView class]]);
    ACRInputLabelView *labelview = (ACRInputLabelView *)inputView;
    XCTAssertNotNil(labelview.inputView);
    XCTAssertTrue([labelview.inputView isKindOfClass:[UITextField class]]);
    UITextField *textField = (UITextField *)labelview.inputView;
    XCTAssertTrue(textField.isSecureTextEntry);
}

@end

