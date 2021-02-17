//
//  MockRenderer
//  MockRenderer.mm
//
//  Copyright © 2022 Microsoft. All rights reserved.
//

#import "MockRenderer.h"
#import <XCTest/XCTest.h>

@implementation MockRenderer

+ (MockRenderer *)getInstance
{
    static MockRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig
{
    //std::shared_ptr<BaseCardElement> elem = [acoElem element];
    //std::shared_ptr<TextBlock> textBlockElement = std::static_pointer_cast<TextBlock>(elem);
    // get renderers by enum type
    // call the default renderers --> why? so the renderer won't break
    // call container renderer
    // call addtional properties on  acoElem elem
    // check the additional properties on contaienr element
    //
    ACRContainerRenderer *defaultRenderer = [ACRContainerRenderer getInstance];

    UIView *view = [defaultRenderer render:viewGroup rootView:rootView inputs:inputs baseCardElement:acoElem hostConfig:acoConfig];

    NSData *additionalProperty = acoElem.additionalProperty;
    XCTAssertTrue(additionalProperty != nullptr);
    NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:additionalProperty options:NSJSONReadingMutableLeaves error:nil];
    NSNumber *radius = dictionary[@"my.cornerRadius"];
    XCTAssertTrue([radius floatValue] == 20.0f);

    return view;
}
@end
