//
//  ACRCustomActionRenderer
//  ACRCustomActionRenderer.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "ACRCustomActionRenderer.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRRegistration.h"
#import "SharedAdaptiveCard.h"
#import "UnknownAction.h"
#import "UtiliOS.h"

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

- (UIButton *)renderButton:(ACRView *)view
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<UnknownAction> customAction = std::dynamic_pointer_cast<UnknownAction>([acoElem element]);

    ACRRegistration *reg = [ACRRegistration getInstance];
    if (reg) {
        NSString *type = [NSString stringWithCString:customAction->GetElementTypeString().c_str() encoding:NSUTF8StringEncoding];
        NSObject<ACOIBaseActionElementParser> *parser = [reg getCustomActionElementParser:type];
        if (!parser) {
            @throw [ACOFallbackException fallbackException];
        }
        Json::Value blob = customAction->GetAdditionalProperties();
        Json::FastWriter fastWriter;
        NSString *jsonString = [[NSString alloc] initWithCString:fastWriter.write(blob).c_str() encoding:NSUTF8StringEncoding];
        if (jsonString.length > 0) {
            NSData *jsonPayload = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
            ACOParseContext *context = [reg getParseContext];
            ACOBaseActionElement *actionElement = [parser deserialize:jsonPayload parseContext:context];
            ACRBaseActionElementRenderer *renderer = [reg getActionRenderer:[NSNumber numberWithLong:type.hash]];
            ;
            if (renderer) {
                return [renderer renderButton:view inputs:inputs superview:superview baseActionElement:actionElement hostConfig:acoConfig];
            }
        }
    }
    return nil;
}

@end
