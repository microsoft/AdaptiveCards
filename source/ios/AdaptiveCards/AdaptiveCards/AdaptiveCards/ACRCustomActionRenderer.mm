//
//  ACRCustomActionRenderer
//  ACRCustomActionRenderer.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "ACRCustomActionRenderer.h"
#import "ACRRendererPrivate.h"
#import "UnknownElement.h"
#import "SharedAdaptiveCard.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACOHostConfigPrivate.h"

@implementation ACRCustomActionRenderer

+ (ACRCustomActionRenderer *)getInstance
{
    static ACRCustomActionRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRActionType)elemType
{
    return ACRUnknownAction;
}

- (UIButton* )renderButton:(ACRView *)view
                    inputs:(NSArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    //std::shared_ptr<UnknownElement> customElem = std::dynamic_pointer_cast<UnknownElement>([acoElem element]);
    //Json::Value blob = customElem->GetAdditionalProperties();
    //Json::FastWriter fastWriter;
    //NSString *key = [[NSString alloc] initWithCString:customElem->GetElementTypeString() encoding:NSUTF8StringEncoding];
    //customParser = [registration getCustomActionElementParser:key];
    //customParseer deserialize
    //[view getParseContext]->actionParserRegistration.GetParser("TextBlock");
/*
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
 */
    return nil;
}

@end
