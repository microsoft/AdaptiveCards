//
//  AdaptiveCardsTextBlockTests.m
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "TextBlock.h"
#import "Enums.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface AdaptiveCardsTextBlockTests : XCTestCase

@end

@implementation AdaptiveCardsTextBlockTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testTextBlockTextProperty {
    std::shared_ptr<AdaptiveCards::TextBlock> textblock = std::make_shared<AdaptiveCards::TextBlock>();
    textblock->SetText("Text test");
    XCTAssert(textblock->GetText() == "Text test");
}

- (void)testTextBlockTextPropertySerialization {
    std::shared_ptr<AdaptiveCards::TextBlock> textblock = std::make_shared<AdaptiveCards::TextBlock>();
    textblock->SetText("Text test");
    XCTAssert(textblock->Serialize() == "{\"text\":\"Text test\",\"type\":\"TextBlock\"}\n");
}

- (void)verifyTextColorIsSet : (AdaptiveCards::ForegroundColor) color
                 onTextBlock : (std::shared_ptr<AdaptiveCards::TextBlock> &) textblock{
    textblock->SetTextColor(color);
    XCTAssert(textblock->GetTextColor() == color);
}

- (void)testTextBlockColorProperty {
    std::shared_ptr<AdaptiveCards::TextBlock> textblock = std::make_shared<AdaptiveCards::TextBlock>();
    [self verifyTextColorIsSet : AdaptiveCards::ForegroundColor::Default
                   onTextBlock : textblock];
    [self verifyTextColorIsSet : AdaptiveCards::ForegroundColor::Dark
                   onTextBlock : textblock];
    [self verifyTextColorIsSet : AdaptiveCards::ForegroundColor::Light
                   onTextBlock : textblock];
    [self verifyTextColorIsSet : AdaptiveCards::ForegroundColor::Accent
                   onTextBlock : textblock];
    [self verifyTextColorIsSet : AdaptiveCards::ForegroundColor::Good
                   onTextBlock : textblock];
    [self verifyTextColorIsSet : AdaptiveCards::ForegroundColor::Warning
                   onTextBlock : textblock];
    [self verifyTextColorIsSet : AdaptiveCards::ForegroundColor::Attention
                   onTextBlock : textblock];
}

- (void)verifyTextColorIsSerialized : (AdaptiveCards::ForegroundColor) color
                                 as : (const std::string &) serializedString
                        onTextBlock : (std::shared_ptr<AdaptiveCards::TextBlock> &) textblock {
    textblock->SetTextColor(color);
    std::string serializedTextBlock = textblock->Serialize();
    XCTAssert(serializedTextBlock == "{\"color\":\"" + serializedString + "\",\"text\":\"\",\"type\":\"TextBlock\"}\n");
}

- (void)testTextBlockColorPropertySerialization {
    std::shared_ptr<AdaptiveCards::TextBlock> textblock = std::make_shared<AdaptiveCards::TextBlock>();
    XCTAssert(textblock->Serialize() == "{\"text\":\"\",\"type\":\"TextBlock\"}\n");
    
    [self verifyTextColorIsSerialized : AdaptiveCards::ForegroundColor::Dark
                                   as : "Dark"
                          onTextBlock : textblock];
    [self verifyTextColorIsSerialized : AdaptiveCards::ForegroundColor::Light
                                   as : "Light"
                               onTextBlock : textblock];
    [self verifyTextColorIsSerialized : AdaptiveCards::ForegroundColor::Accent
                                   as : "Accent"
                          onTextBlock : textblock];
    [self verifyTextColorIsSerialized : AdaptiveCards::ForegroundColor::Good
                                   as : "Good"
                          onTextBlock : textblock];
    [self verifyTextColorIsSerialized : AdaptiveCards::ForegroundColor::Warning
                                   as : "Warning"
                          onTextBlock : textblock];
    [self verifyTextColorIsSerialized : AdaptiveCards::ForegroundColor::Attention
                                   as : "Attention"
                          onTextBlock : textblock];
}

@end
