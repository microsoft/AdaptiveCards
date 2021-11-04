//
//  ACRCustomColumnView.m
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRCustomRenderers.h"

@implementation ACRCustomColumnRenderer

+ (ACRCustomColumnRenderer *)getInstance
{
    static ACRCustomColumnRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    UIView *view = [super render:viewGroup rootView:rootView inputs:inputs baseCardElement:acoElem hostConfig:acoConfig];
    if (acoElem.additionalProperty) {
        NSError *error = nil;
        id props = [NSJSONSerialization JSONObjectWithData:acoElem.additionalProperty options:0 error:&error];
        self.fetchActualRenderedView(view, props);
    }
    return view;
}

@synthesize fetchActualRenderedView;

@end

@implementation ACRCustomContainerRenderer

+ (ACRCustomContainerRenderer *)getInstance
{
    static ACRCustomContainerRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    UIView *view = [super render:viewGroup rootView:rootView inputs:inputs baseCardElement:acoElem hostConfig:acoConfig];
    if (acoElem.additionalProperty) {
        NSError *error = nil;
        id props = [NSJSONSerialization JSONObjectWithData:acoElem.additionalProperty options:0 error:&error];
        self.fetchActualRenderedView(view, props);
    }
    return view;
}

@synthesize fetchActualRenderedView;

@end
