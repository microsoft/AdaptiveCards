//
//  AdaptiveCardsTests.mm
//  AdaptiveCardsTests
//
//  Created by almedina on 6/22/21.
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "TextBlock.h"
#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

@interface AdaptiveCardsTests : XCTestCase

@end

@implementation AdaptiveCardsTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testTextBlockTextProperty2 {
    std::shared_ptr<AdaptiveCards::TextBlock> textblock = std::make_shared<AdaptiveCards::TextBlock>();
    textblock->SetText("Text test");
    
    XCTAssert(textblock->GetText() == "Text test");
    
    std::string serializedTextBlock = textblock->Serialize();
    XCTAssert(serializedTextBlock == "{\"text\":\"Text test\",\"type\":\"TextBlock\"}\n");
}

@end

