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
