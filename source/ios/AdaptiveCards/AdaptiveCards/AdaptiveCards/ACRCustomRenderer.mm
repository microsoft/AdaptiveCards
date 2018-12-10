//
//  ACRCustomRenderer
//  ACRCustomRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRCustomRenderer.h"
#import "ACRRendererPrivate.h"
#import "UnknownElement.h"
#import "SharedAdaptiveCard.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACOHostConfigPrivate.h"

@implementation ACRCustomRenderer

+ (ACRCustomRenderer *)getInstance
{
    static ACRCustomRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRUnknown;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<UnknownElement> customElem = std::dynamic_pointer_cast<UnknownElement>([acoElem element]);
    Json::Value blob = customElem->GetAdditionalProperties();
    Json::FastWriter fastWriter;

    NSString *jsonString = [[NSString alloc] initWithCString:fastWriter.write(blob).c_str() encoding:NSUTF8StringEncoding];
    if(jsonString.length > 0){
        NSData *jsonPayload = nil;
        jsonPayload = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
        if(jsonPayload && self.customElementParser &&
            [self.customElementParser respondsToSelector: @selector(deserializeToCustomUIElement:)]){
            UIView *customUIElement = [self.customElementParser deserializeToCustomUIElement:jsonPayload];
            ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:customUIElement.frame];
            wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
            [wrappingview addSubview:customUIElement];
            [wrappingview addConstraints:[ACOHostConfig getConstraintsForImageAlignment:HorizontalAlignment::Center
                                                                          withSuperview:wrappingview
                                                                                 toView:customUIElement]];
            [viewGroup addArrangedSubview:wrappingview];
        }
    }

    return viewGroup;
}

@end
